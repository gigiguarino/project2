#!/bin/sh

cd eecs478p2
make clean
make

./project2 -absmin9x12y dp.blif

cd ..
cd sim

for i in {1..17}
do
./simulator ../eecs478p2/dp.blif < ../datapath_inputs/test$i.txt > ../datapath_sim_outputs/test$i_sim_out.txt
done

cd ..

for i in {1..17}
do
echo "Comparing test $i"
diff datapath_outputs/test$i_out.txt datapath_sim_outputs/test$i_sim_out.txt
echo "\n\n"
done

