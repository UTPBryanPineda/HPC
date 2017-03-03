#!/bin/bash

#SBATCH --job-name=multimatriz
#SBATCH --output=res_mpi_multimatriz.out
#SBATCH --ntasks=2
#SBATCH --nodes=2
#SBATCH --time=10:00
#SBATCH --mem-per-cpu=100
#SBATCH --gres=gpu:1

mpirun multimatriz
