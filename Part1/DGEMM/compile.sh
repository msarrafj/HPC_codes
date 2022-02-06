#compile
icc -o dgemm dgemm.c -I /opt/packages/OpenBLAS/0.2.19/include/ -L /opt/packages/OpenBLAS/0.2.19/lib -lopenblas

#run
./dgemm 256 256 256