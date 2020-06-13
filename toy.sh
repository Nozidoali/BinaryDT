
./DT/BinaryDT train Benchmarks/toy.train.pla Results/toy.aag
./Aiger/aigtoaig Results/toy.aag Results/toy.aig
./abc/abc -c "&read Results/toy.aig; &ps; &mltest Benchmarks/toy.train.pla" | \
     sed -n 's/.*\((.*%)\).*\((.*%)\).*/\1/p' | \
     sed -n 's/(\(.*\))/\1/p' >> result.csv
