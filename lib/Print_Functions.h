#ifndef Print_Functions_H
#define Print_Functions_H

#include <iostream>
#include <iomanip>

#define PRECISION 3

template<typename SeqIt>
void printNElem(SeqIt firstElem, int N)
{
  std::cout << std::fixed << std::setprecision(PRECISION);
  auto x_i = firstElem;
  for( int i = 0; i < N; ++i)
    std::cout << *(x_i+i) << ", ";
  std::cout << "..." << std::endl;
}

template<typename SeqIt>
void printTime(SeqIt firstElem, SeqIt lastElem)
{
  std::cout << std::fixed << std::setprecision(PRECISION);
  std::cout << "Processor | comm. time | comp. time | total time\n";
  std::cout << "__________|____________|____________|___________\n";
  int cnt = 0;
  for(auto x_i = firstElem; x_i < lastElem; x_i += 3)
    std::cout << std::setfill(' ') << std::setw(9) << cnt++ << " | "
    << std::setfill(' ') << std::setw(10) << *(x_i) << " | "
    << std::setfill(' ') << std::setw(10) << *(x_i+1) << " | "
    << std::setfill(' ') << std::setw(10) << *(x_i+2) << "\n";
  std::cout << std::endl;
}

template<typename SeqIt>
void printArray2D(int m, int n, SeqIt firstElem, SeqIt lastElem)
{
  std::cout << std::fixed << std::setprecision(PRECISION);
  std::cout << "Array = \n( ";
  int nextline = 0;
  for(auto x_it = firstElem; x_it < lastElem; ++x_it)
  {
    if (n == nextline)
    {
      std::cout << "\n  ";
      nextline = 0;
    }
    std::cout << std::setfill(' ') << std::setw(7) << *x_it;

    if (x_it+1 != lastElem)
      std::cout << ", ";

    nextline++;
  }
  std::cout << " )" << std::endl;
}

#endif /* end of include guard: Print_Functions_H */
