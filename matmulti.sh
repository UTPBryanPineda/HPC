#!/bin/bash
#
#SBATCH --job-name=matmultislurm
#SBATCH --output=res_mat_multi_slurm.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=8
#SBATCH --time=10:00
#SBATCH --mem-per-cpu=100

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./MultMatrParalel
