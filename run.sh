#!/bin/bash
#SBATCH --job-name=Thermal_conduction
#SBATCH --partition=s_hadoop
#SBATCH --nodes=16
#SBATCH --ntasks-per-node=1
#SBATCH --time=30:00
mpirun ./non_Block.exe 4096 64 4000
