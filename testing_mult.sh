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

./simulator ../mult_outputs/mult2.blif < ../mult_inputs/test1.txt > ../mult_sim_outs/test1_sim_out.txt

./simulator ../mult_outputs/mult3.blif < ../mult_inputs/test2.txt > ../mult_sim_outs/test2_sim_out.txt

./simulator ../mult_outputs/mult4.blif < ../mult_inputs/test3.txt > ../mult_sim_outs/test3_sim_out.txt

./simulator ../mult_outputs/mult5.blif < ../mult_inputs/test4.txt > ../mult_sim_outs/test4_sim_out.txt

./simulator ../mult_outputs/mult12.blif < ../mult_inputs/test5.txt > ../mult_sim_outs/test5_sim_out.txt

./simulator ../mult_outputs/mult16.blif < ../mult_inputs/test6.txt > ../mult_sim_outs/test6_sim_out.txt

echo "Comparing test1"
diff ../mult_test_outs/test1_out.txt ../mult_sim_outs/test1_sim_out.txt
echo "\n\n"

echo "Comparing test2"
diff ../mult_test_outs/test2_out.txt ../mult_sim_outs/test2_sim_out.txt
echo "\n\n"

echo "Comparing test3"
diff ../mult_test_outs/test3_out.txt ../mult_sim_outs/test3_sim_out.txt
echo "\n\n"

echo "Comparing test4"
diff ../mult_test_outs/test4_out.txt ../mult_sim_outs/test4_sim_out.txt
echo "\n\n"

echo "Comparing test5"
diff ../mult_test_outs/test5_out.txt ../mult_sim_outs/test5_sim_out.txt
echo "\n\n"

echo "Comparing test6"
diff ../mult_test_outs/test6_out.txt ../mult_sim_outs/test6_sim_out.txt
echo "\n\n"
