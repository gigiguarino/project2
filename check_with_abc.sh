

cd abc70930

for i in {1..32}
do
    echo "cec ../adder_blifs/add$i.blif ../add_outputs/add$i.blif" | ./abc
done

for i in {1..32}
do
    echo "cec ../sub_blifs/sub$i.blif ../sub_outputs/sub$i.blif" | ./abc
done







