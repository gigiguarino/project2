#!/bin/sh

cd sim

for i in {1..13}
do
echo "TEST $i"
./simulator ../dp.blif < ../datapath_inputs/test$i.txt
echo "---"
echo "---"
echo "---"
echo "---"
done



