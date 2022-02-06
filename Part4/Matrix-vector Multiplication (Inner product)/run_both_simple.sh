echo "--------------------------------------------------"
echo "Using optimization O0"
icc -O0 matVecMul_both_simple.c -o vec_both -qopenmp
echo "-------------------------"
./vec_both
echo "--------------------------------------------------"
# echo "--------------------------------------------------"
# echo "Using optimization O2"
# icc -O2 matVecMul_both_simple.c -o vec_both -qopenmp
# echo "-------------------------"
# ./vec_both
# echo "--------------------------------------------------"
# echo "--------------------------------------------------"
# echo "Using optimization O3"
# icc -O3 matVecMul_both_simple.c -o vec_both -qopenmp
# echo "-------------------------"
# ./vec_both
# echo "-------------------------"
# echo "--------------------------------------------------"
