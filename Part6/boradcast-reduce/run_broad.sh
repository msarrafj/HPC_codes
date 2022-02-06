mpicc broadcast.c -o broad
echo "Run for 2 prcs"
mpirun -np 2 broad
echo "---------------------------------------------------------------"
echo "Run for 4 prcs"
mpirun -np 4 broad
echo "---------------------------------------------------------------"
echo "Run for 8 prcs"
mpirun -np 8 broad
echo "---------------------------------------------------------------"
echo "Run for 16 prcs"
mpirun -np 16 broad
echo "---------------------------------------------------------------"
echo "Run for 28 prcs"
mpirun -np 28 broad
echo "---------------------------------------------------------------"
echo "Run for 56 prcs"
mpirun -np 56 broad
echo "---------------------------------------------------------------"

