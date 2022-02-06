moodule load papi
icc my_papi.c -o my_papi -qopenmp -I/opt/packages/papi/5.4.3/include/ -O0 -L/opt/packages/papi/5.4.3/lib/ -lpapi
