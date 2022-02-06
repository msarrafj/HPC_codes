echo "--------------------------------------------------"
echo "Using optimization O0"
icc -O0 matVecMul_inner_sum_private.c -o vec_sum_private -qopenmp
echo "-------------------------"
./vec_sum_private
echo "--------------------------------------------------"
# echo "--------------------------------------------------"
# echo "Using optimization O2"
# icc -O2 matVecMul_inner_sum_private.c -o vec_sum_private -qopenmp
# echo "-------------------------"
# ./vec_sum_private
# echo "--------------------------------------------------"
# echo "--------------------------------------------------"
# echo "Using optimization O3"
# icc -O3 matVecMul_inner_sum_private.c -o vec_sum_private -qopenmp
# echo "-------------------------"
# ./vec_sum_private
# echo "-------------------------"
# echo "--------------------------------------------------"
