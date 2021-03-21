#ifndef MPI_Init_Fin_H
#define MPI_Init_Fin_H

#include <mpi.h>

class MPI_Init_Fin
{
public:
  MPI_Init_Fin(int* argc, char ***argv)
  {
    int ret = MPI_Init(argc, argv); // MPI initialisieren
    if (ret != MPI_SUCCESS)
    {
      MPI_Abort(MPI_COMM_WORLD,ret); // MPI-Programm abbrechen
    }
  }

  ~MPI_Init_Fin() {
    MPI_Finalize(); // MPI sauber aufraeumen
  }
};

#endif /* end of include guard: MPI_Init_Fin */
