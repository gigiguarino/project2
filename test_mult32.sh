

echo "starting"

for i in {1..1000}
do
    for j in {1000..2000}
    do
        echo "obase=2;$i" | bc >> sim/input.txt
        echo "obase=2;$j" | bc >> sim/input.txt
        cd sim
        ./simulator ../mult_outputs/mult32.blif < input.txt
        cd ..
        n=$((i*j))
        echo $n
        rm sim/input.txt
        echo "---"
        echo "---"
        echo "---"
    done
done
