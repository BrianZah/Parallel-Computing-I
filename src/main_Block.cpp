#include <mpi.h>

#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
#include <cmath>
#include <string>

#include "MPI_Init_Fin.h"
#include "Print_Functions.h"
#include "InitField.h"
#include "GetMargin.h"
#include "Stencil.h"
#include "ExtractBlock.h"
#include "InsertBlock.h"
#include "SortField.h"
#include "CreatePPM.h"

int main(int argc, char* argv[])
{
// PART 1: PREPARATION
// Initialising MPI
    MPI_Init_Fin mpi_init_fin(&argc, &argv);
    int num, rank;
    int root = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &num) ; // Anzahl der Prozesse
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Prozessnummer

// Initialising
  if (4 != argc)
  {
    if (root == rank)
      std::cerr << "usage: " << argv[0] << "<n> <local iterations (g)> <global iterations>" << std::endl;
    return -1;
  }
  int n, g, iter;

  if ( !(std::istringstream(argv[1]) >> n) || !(n > 0) ||
       !(std::istringstream(argv[2]) >> g) || !(g >= 0) ||
       !(std::istringstream(argv[3]) >> iter) || !(iter >= 0) )
  {
    if (root == rank)
      std::cerr << "arguments are not a valid positive integer" << std::endl;
    return -1;
  }

// Preparing MPI-operations
  const int sqrt_num = std::sqrt(num);
  const int n_block = n/sqrt_num;

  if (sqrt_num != std::sqrt(num))
  {
    if (root == rank)
      std::cerr << "number of processes has to be a squarenumber" << std::endl;
    return -1;
  }

  if (n_block != 1.0*n/sqrt_num)
  {
    if (root == rank)
      std::cerr << "n / sqrt( #processes ) has to be an integer" << std::endl;
    return -1;
  }

  const int x_pos = rank%sqrt_num;
  const int y_pos = rank/sqrt_num;

  int upper_margin, under_margin, left_margin, right_margin;
  getMargin(x_pos, y_pos, sqrt_num, g,
    upper_margin, under_margin, left_margin, right_margin);

  const int m_dim = n_block + upper_margin + under_margin;
  const int n_dim = n_block + left_margin + right_margin;

  std::vector<float> Block(m_dim * n_dim);
  std::vector<float> Block_help(m_dim * n_dim);

  std::vector<float> Cols_send(n_block * g);
  std::vector<float> Cols_recv(n_block * g);
  std::vector<float> Rows_send(g * n_dim);
  std::vector<float> Rows_recv(g * n_dim);

  std::vector<float> Block_send(n_block * n_block);
  std::vector<float> Field_recv(n * n);

// Initaialize computational Block
  initField(Block.begin(), m_dim, n_dim, x_pos, y_pos, sqrt_num);
// Preparing computation / communication
  double dt = 0.1;
  double h_2 = 1.0 / (n*n);
  double alpha = 0.25*h_2 / dt;

  MPI_Status s;
// Preparing time measurement
  auto clock = std::chrono::high_resolution_clock();
  auto T0 = clock.now();
  auto t0 = clock.now();
  auto t1 = clock.now();
  double time_comm = 0.0;
  double time_comp = 0.0;
// PART 2: MAIN LOOP
  for (int i = 0; i < iter; ++i)
  {
  /*
  if (root == rank)
      std::cout << "Processing iteration " << i+1 << " of " << iter << "\n";
  */
// Sending and receiving in x-direction
    t0 = clock.now();
    if (sqrt_num-1 != x_pos)
    {
      extractBlock(Block.begin(), upper_margin, left_margin+n_block-right_margin, right_margin,
                  Cols_send.begin(), n_block, g);
      MPI_Send(Cols_send.data(), n_block*g, MPI_FLOAT, rank+1, i, MPI_COMM_WORLD);
    }
    if ( 0 != x_pos)
    {
      MPI_Recv(Cols_recv.data(), n_block*g, MPI_FLOAT, rank-1, i, MPI_COMM_WORLD, &s);
      extractBlock(Block.begin(), upper_margin, left_margin, n_block-left_margin+right_margin,
                  Cols_send.begin(), n_block, g);
      MPI_Send(Cols_send.data(), n_block*g, MPI_FLOAT, rank-1, i, MPI_COMM_WORLD);
      insertBlock(Cols_recv.begin(), n_block, g,
        Block.begin(), upper_margin, 0, n_block + right_margin);
    }
    if (sqrt_num-1 != x_pos)
    {
      MPI_Recv(Cols_recv.data(), n_block*g, MPI_FLOAT, rank+1, i, MPI_COMM_WORLD, &s);
      insertBlock(Cols_recv.begin(), n_block, g,
        Block.begin(), upper_margin, left_margin + n_block, 0);
    }
// Sending and receiving in y-direction
    if (sqrt_num-1 != y_pos)
    {
      extractBlock(Block.begin(), upper_margin+n_block-under_margin, 0, 0,
                  Rows_send.begin(), g, n_dim);
      MPI_Send(Rows_send.data(), g*n_dim, MPI_FLOAT, rank+sqrt_num, i, MPI_COMM_WORLD);
    }
    if ( 0 != y_pos)
    {
      MPI_Recv(Rows_recv.data(), g*n_dim, MPI_FLOAT, rank-sqrt_num, i, MPI_COMM_WORLD, &s);
      extractBlock(Block.begin(), upper_margin, 0, 0,
                  Rows_send.begin(), g, n_dim);
      MPI_Send(Rows_send.data(), g*n_dim, MPI_FLOAT, rank-sqrt_num, i, MPI_COMM_WORLD);
      insertBlock(Rows_recv.begin(), g, n_dim,
        Block.begin(), 0, 0, 0);
    }
    if (sqrt_num-1 != y_pos)
    {
      MPI_Recv(Rows_recv.data(), g*n_dim, MPI_FLOAT, rank+sqrt_num, i, MPI_COMM_WORLD, &s);
      insertBlock(Rows_recv.begin(), g, n_dim,
        Block.begin(), upper_margin+n_block, 0, 0);
    }
    t1 = clock.now();
    time_comm += std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count()/1.0E9;
// Preparing and performing stencil computation
    t0 = clock.now();
    if (0 == i) std::copy(Block.begin(), Block.end(), Block_help.begin());
    for (int g_i = 0; g_i < g; ++g_i)
    {
      //stencil(m_dim, n_dim, alpha, dt, h_2, Block.begin(), Block_help.begin());
      borderedStencil(m_dim, n_dim, g_i,
        (0 == y_pos), (sqrt_num-1 == y_pos), (0 == x_pos), (sqrt_num-1 == x_pos),
        alpha, dt, h_2, Block.begin(), Block_help.begin());
      std::swap(Block, Block_help);
    }
    t1 = clock.now();
    time_comp += std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count()/1.0E9;
  }
// PART 3: PREPARATION AND OUTPUT OF THE RESULTS
// Collecting array for printing
  extractBlock(Block.begin(), upper_margin, left_margin, right_margin,
             Block_send.begin(), n_block, n_block);
  MPI_Gather(Block_send.data(), n_block*n_block, MPI_FLOAT,
        Field_recv.data(), n_block*n_block, MPI_FLOAT, 0, MPI_COMM_WORLD);
// Stop and collect time and print array
  auto T1 = clock.now();
  auto time_total = std::chrono::duration_cast<std::chrono::nanoseconds>(T1 - T0).count()/1.0E9;
  double time_buffer[] = {time_comm, time_comp, time_total};
  std::vector<double> time(3*num);
  MPI_Gather(time_buffer, 3, MPI_DOUBLE,
        time.data(), 3, MPI_DOUBLE, 0, MPI_COMM_WORLD);
// Print (, sort, and save) results
if (root == rank)
  {
    std::cout << n << " " << g << " " << iter << "\n";
    printTime(time.begin(), time.end());

    std::vector<float> Field(n * n);
    sortField(n, Field.begin(), n_block, Field_recv.begin(), sqrt_num);
    //printArray2D(n, n, Field.begin(), Field.end());
    std::string filename = std::to_string(n) + "_" + std::to_string(g) + "_" + std::to_string(iter)
                          + "_blocking_time:_" + std::to_string(time_total) + ".ppm";
    createPPM(Field.begin(), n, filename.data());

  }

  return 0;
}
