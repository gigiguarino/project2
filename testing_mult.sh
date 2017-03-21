#!/bin/sh

cd eecs478p2
make clean
make

#test1 is 2 bit
#test2 is 3 bit
#test3 is 4 bit
#test4 is 5 bit
#test5 is 12 bit
#test6 is 16 bit

cd ..
cd sim

echo "Test1:"
echo "Sim output:"
./simulator ../mult_outputs/mult2.blif < ../mult_inputs/test1.txt 
echo "Desired output:"
cat ../mult_test_outs/test1_out.txt
echo "-- "
echo "-- "
echo "-- "

echo "Test2:"
echo "Sim output:"
./simulator ../mult_outputs/mult3.blif < ../mult_inputs/test2.txt 
echo "Desired output:"
cat ../mult_test_outs/test2_out.txt
echo "-- "
echo "-- "
echo "-- "

echo "Test3:"
echo "Sim output:"
./simulator ../mult_outputs/mult4.blif < ../mult_inputs/test3.txt 
echo "Desired output:"
cat ../mult_test_outs/test3_out.txt
echo "-- "
echo "-- "
echo "-- "

echo "Test4:"
echo "Sim output:"
./simulator ../mult_outputs/mult5.blif < ../mult_inputs/test4.txt 
echo "Desired output:"
cat ../mult_test_outs/test4_out.txt
echo "-- "
echo "-- "
echo "-- "

echo "Test5:"
echo "Sim output:"
./simulator ../mult_outputs/mult12.blif < ../mult_inputs/test5.txt 
echo "Desired output:"
cat ../mult_test_outs/test5_out.txt
echo "-- "
echo "-- "
echo "-- "

echo "Test6:"
echo "Sim output:"
./simulator ../mult_outputs/mult16.blif < ../mult_inputs/test6.txt 
echo "Desired output:"
cat ../mult_test_outs/test6_out.txt
echo "-- "
echo "-- "
echo "-- "

