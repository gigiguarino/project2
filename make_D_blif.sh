#!/bin/bash

rm datapath.blif
echo >> datapath.blif

echo "making datapath.blif..."
g++ make_blifs.cpp -o make_blif
./make_blif 0 datapath > datapath.blif

echo "done! :-)"






