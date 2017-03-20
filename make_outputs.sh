#!/bin/sh
chmod +x make_outputs.sh

# remove all old outputs
cd add_outputs
rm *
cd ../sub_outputs
rm *
cd ../mult_outputs
rm *
cd ..

# create new ones
cd eecs478p2
make clean
make

for i in {1..32}
do
echo >> ../add_outputs/add$i.blif
./project2 -add $i ../add_outputs/add$i.blif
done

for i in {1..32}
do
echo >> ../sub_outputs/sub$i.blif
./project2 -sub $i ../sub_outputs/sub$i.blif
done

for i in {1..32}
do
echo >> ../mult_outputs/mult$i.blif
./project2 -mult $i ../mult_outputs/mult$i.blif
done

