

cd sim
for i in {1..16}
do
./simulator ../abs_outputs/abs4.blif < ../abs_inputs/test$i.txt
done
