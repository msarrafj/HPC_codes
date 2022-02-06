CC = icc
OPT = -O2
ARRAY_SIZE = -DSTREAM_ARRAY_SIZE

#array size 10 million elements
SIZE = 100


stream: stream.c
	$(CC) $(OPT) $(ARRAY_SIZE)=$(SIZE) stream.c -o stream

clean:
	rm -f stream_f.exe stream_c.exe *.o

# an example of a more complex build line for the Intel icc compiler
# stream.icc: stream.c
# 	icc -O3 -xCORE-AVX2 -ffreestanding -qopenmp -DSTREAM_ARRAY_SIZE=80000000 -DNTIMES=20 stream.c -o stream.omp.AVX2.80M.20x.icc
