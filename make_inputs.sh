#!/bin/sh

# remove all old input files
for i in {1..32}
do
  cd add_inputs/add$i
  rm -f *
  cd ../../sub_inputs/sub$i
  rm -f *
  cd ../../mult_inputs/mult$i
  rm -f *
  cd ../..
done

# creating add inputs
for j in {1..8}
do
  for i in {1..32}
  do
    for k in $(seq 1 $i)
    do
      printf "%d" $(($RANDOM%2)) >> add_inputs/add$i/add$j.txt
    done
    printf "\n" >> add_inputs/add$i/add$j.txt
    for k in $(seq 1 $i)
    do
      printf "%d" $(($RANDOM%2)) >> add_inputs/add$i/add$j.txt
    done
    printf "\n" >> add_inputs/add$i/add$j.txt
    printf "%d" $(($RANDOM%2)) >> add_inputs/add$i/add$j.txt
  done
done

# creating sub inputs
for j in {1..8}
do
  for i in {1..32}
  do
    for k in $(seq 1 $i)
    do
      printf "%d" $(($RANDOM%2)) >> sub_inputs/sub$i/sub$j.txt
    done
    printf "\n" >> sub_inputs/sub$i/sub$j.txt
    for k in $(seq 1 $i)
    do
      printf "%d" $(($RANDOM%2)) >> sub_inputs/sub$i/sub$j.txt
    done
  done
done


# creating mult inputs 1-14
for j in {1..8}
do
  for i in {1..32}
  do
    for k in $(seq 1 $i)
    do
      printf "%d" $(($RANDOM%2)) >> mult_inputs/mult$i/mult$j.txt
    done
    printf "\n" >> mult_inputs/mult$i/mult$j.txt
    for k in $(seq 1 $i)
    do
      printf "%d" $(($RANDOM%2)) >> mult_inputs/mult$i/mult$j.txt
    done
  done
done

