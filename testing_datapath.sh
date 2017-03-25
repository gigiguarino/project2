#!/bin/sh

cd sim

for i in {9,11,2,4}
do
echo "TEST $i"
./simulator ../dp.blif < ../datapath_inputs/test$i.txt
echo "---"
echo "---"
echo "---"
echo "---"
done



