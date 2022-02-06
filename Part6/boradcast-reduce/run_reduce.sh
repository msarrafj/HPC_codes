mpicc reduce.c -o red
echo "Run for 2 prcs"
mpirun -np 2 ./red
echo "---------------------------------------------------------------"
echo "Run for 4 prcs"
mpirun -np 4 ./red
echo "---------------------------------------------------------------"
echo "Run for 8 prcs"
mpirun -np 8 ./red
echo "---------------------------------------------------------------"
echo "Run for 16 prcs"
mpirun -np 16 ./red
echo "---------------------------------------------------------------"
echo "Run for 28 prcs"
mpirun -np 28 ./red
echo "---------------------------------------------------------------"
echo "Run for 56 prcs"
mpirun -np 56 ./red
echo "---------------------------------------------------------------"

