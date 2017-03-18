#!/bin/sh

cd abc70930
make clean
make

for i in {1..32}
do
cec ../add_outputs/add$i.blif ../adder_blifs/add$i.blif
done

for i in {1..32}
do
cec ../sub_outputs/sub$i.blif ../sub_blifs/sub$i.blif
done

for i in {1..2}
do
cec ../mult_outputs/mult$i.blif ../mult_blifs/mult$i.blif
done
