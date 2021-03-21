# What's the project about and how to run it?
The goal of the project was to gain insight into development environments with multiple nodes. Therefore, a stencil code applying the Message Parsing Interface (MPI) was created. To built the program, the provided cmake-file can be used. After, the code can be executed eighter by running the slurm-script "run.sh" on a corresponding environment or using the mpirun command on a local machine. When running the program on a local machine, the number of mpi-processes can be modified through the "Hostfile". Thus, a possible execution command could be:

```cmd
mpirun –hostfile ./Hostfile ./non_Block.exe 512 64 500
```

**Further information can be found in the uploaded paper "MPI_Implementation_of_the_two_dimensional_heat_equation.pdf" within the "Paper" folder.**
