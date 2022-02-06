echo "--------------------------------------------------"
echo "Using optimization O0"
icc -O0 matVecMul_outer_simple.c -o vec_outer -qopenmp
echo "-------------------------"
./vec_outer
echo "--------------------------------------------------"
echo "--------------------------------------------------"
# echo "Using optimization O2"
# icc -O2 matVecMul_outer_simple.c -o vec_outer -qopenmp
# echo "-------------------------"
# ./vec_outer
# echo "--------------------------------------------------"
# echo "--------------------------------------------------"
# echo "Using optimization O3"
# icc -O3 matVecMul_outer_simple.c -o vec_outer -qopenmp
# echo "-------------------------"
# ./vec_outer
# echo "-------------------------"
# echo "--------------------------------------------------"
