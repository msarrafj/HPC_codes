gcc -I/opt/packages/papi/5.4.3/include/ -O0 papi_sample.c -L/opt/packages/papi/5.4.3/lib/ -lpapi -o PAPI_SAMPLE
module load papi
srun ./PAPI_SAMPLE 10
