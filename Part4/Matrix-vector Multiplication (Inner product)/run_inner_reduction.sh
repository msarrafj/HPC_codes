echo "--------------------------------------------------"
echo "Using optimization O0"
icc -O0 matVecMul_inner_reduction.c -o vec_red -qopenmp
echo "-------------------------"
./vec_red
echo "--------------------------------------------------"
# echo "--------------------------------------------------"
# echo "Using optimization O2"
# icc -O2 matVecMul_inner_reduction.c -o vec_red -qopenmp
# echo "-------------------------"
# ./vec_red
# echo "--------------------------------------------------"
# echo "--------------------------------------------------"
# echo "Using optimization O3"
# icc -O3 matVecMul_inner_reduction.c -o vec_red -qopenmp
# echo "-------------------------"
# ./vec_red
# echo "-------------------------"
# echo "--------------------------------------------------"
