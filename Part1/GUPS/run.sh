#compile
mpicc gups_opt.c -o gups_opt

#run
mpirun -n 8 ./gups_opt 15 20

#compile
mpicc gups_vanilla.c -o gups_vanilla

#run
mpirun -n 8 ./gups_vanilla 15 20 1024