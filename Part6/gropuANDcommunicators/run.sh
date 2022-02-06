module load mpi/gcc_openmpi
echo "Run for 16 procs"
mpicc exercise3_4.c -o ex3_4
#mpirun -np 4 --rankfile rankfile ex3_4
mpirun -np 16 --map-by ppr:8:node ex3_4
echo "-----------------------------------------"
# echo "Run for 8 procs"
# mpicc exercise3_8.c -o ex3_8
# mpirun -np 8 ex3_8
# echo "-----------------------------------------"
# echo "Run for 16 procs"
# mpicc exercise3_16.c -o ex3_16
# mpirun -np 16 ex3_16
# echo "-----------------------------------------"
# echo "Run for 32 procs"
# mpicc exercise3_32.c -o ex3_32
# mpirun -np 32 ex3_32
# echo "-----------------------------------------"
# echo "Run for 64 procs"
# mpicc exercise3_64.c -o ex3_64
# mpirun -np 64 ex3_64
# echo "-----------------------------------------"
