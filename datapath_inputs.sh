#!/bin/sh

# inputs are 16 bit numbers
# create every possible input
# only need to run this once because inputs aren't going to be
# randomized

cd datapath_inputs
for i in {0..65535}
do
mkdir dp$i
done

# 16 bits
var0=1
var1=2
var2=4
var3=8
var4=16
var5=32
var6=64
var7=128
var8=256
var9=512
var10=1024
var11=2048
var12=4096
var13=8192
var14=16384
var15=32768

for i in {0..65535}
do

for j in {0..65535}
do

s=$i

for k in {0..15}
do
a=$(($s - $((var$k))))
if [ "$a" -gt 0 ]
then
printf "1" >> datapath_inputs/dp$i/dp$j.txt
s=$a
else
printf "0" >> datapath_inputs/dp$i/dp$j.txt
fi
done

printf "\n" >> datapath_inputs/dp$i/dp$j.txt

s=$j

for k in {0..15}
do
b=$(($s - $((var$k))))
if [ "$b" -gt 0 ]
then
printf "1" >> datapath_inputs/dp$i/dp$j.txt
s=$b
else
printf "0" >> datapath_inputs/dp$i/dp$j.txt
fi
done

printf "\n" >> datapath_inputs/dp$i/dp$j.txt

echo "finished datapath input x=$i y=$j"

done
done

