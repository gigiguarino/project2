

cd new_add_blifs
rm *
cd ../new_sub_blifs
rm *
cd ../new_mult_blifs
rm * 
cd ..

g++ make_blifs.cpp -o make_blif

#for i in {1..14}
#do
  #echo "making add$i.blif..."
  #echo >> new_add_blifs/add$i.blif
 # ./make_blif $i add > new_add_blifs/add$i.blif 
#done

#for i in {1..14}
#do
 # echo "making sub$i.blif..."
  #echo >> new_sub_blifs/sub$i.blif
  #./make_blif $i sub > new_sub_blifs/sub$i.blif
#done

for i in {1..16}
do
  echo "making mult$i.blif..."
  echo >> new_mult_blifs/mult$i.blif
  ./make_blif $i mult > new_mult_blifs/mult$i.blif
done

echo "done! :-)"

