#!/bin/sh


# remove all old input files
for i in {1..32}
do
  cd correct_adds/c_add$i
  rm -f *
  cd ../../correct_subs/c_sub$i
  rm -f *
  cd ../../correct_mults/c_mult$i
  rm -f *
  cd ../..
done

cd sim
#simulator creates correct blifs


# making correct adds
for i in {1..32}
do
  for j in {1..8}
  do
    ./simulator ../correct_adds/c_add$i/c_add$j.blif < ../add_inputs/add$i/add$j.txt
  done
done

# making correct subs
for i in {1..32}
do
  for j in {1..8}
  do
    ./simulator ../correct_subs/c_sub$i/c_sub$j.blif < ../sub_inputs/sub$i/sub$j.txt
  done
done

# making correct mults
for i in {1..32}
do
  for j in {1..8}
  do
    ./simulator ../correct_mults/c_mult$i/c_mult$j.blif < ../mult_inputs/mult$i/mult$j.txt
  done
done
