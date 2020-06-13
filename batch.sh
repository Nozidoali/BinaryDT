echo "Index,Node,Accuracy" > result.csv

for i in $(seq 0 99)
do
    i=$(printf "%02d" $i)
    echo "$i / 100\r"
    echo "$i,\c" >> result.csv

    node=$(./DT/BinaryDT train Benchmarks/ex$i.train.pla Results/ex$i.aag | 
        sed -n 's/.*(Node# = \([0-9]*\)).*/\1/p'
    )
    ./Aiger/aigtoaig Results/ex$i.aag Results/ex$i.aig

    percent=$(./abc/abc -c "&read Results/ex$i.aig; &ps; &mltest Benchmarks/ex$i.valid.pla" |
        sed -n 's/.*\((.*%)\).*\((.*%)\).*/\1/p' |
        sed -n 's/(\(.*\))/\1/p')
    echo "$node,\c" >> result.csv
    echo "$percent\c" >> result.csv
    echo "" >> result.csv
done