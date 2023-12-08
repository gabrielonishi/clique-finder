# !/bin/bash
#SBATCH --job-name=maximum_clique_MPI
#SBATCH --nodes=2
#SBATCH --ntasks=3

mpirun ./mpi ../test_graph.txt