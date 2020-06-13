for i in $(seq 1 99)
do
    echo $(printf "%02d" $i)
    ./DT/BinaryDT Benchmarks/ex$i.train.pla Results/ex$i.aag
    ./Aiger/aigtoaig Results/ex$i.aag Results/ex$i.aig
done