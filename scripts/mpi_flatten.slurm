#!/bin/bash
#SBATCH --job-name=maximum_clique_MPI
#SBATCH --nodes=2
#SBATCH --ntasks=6

mpirun ./mpi_flat test_graph.txt
