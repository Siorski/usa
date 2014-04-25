#!/bin/bash
let k=5
let j=5
for ((i=5; $i<3800; i=i+735)) ; do 
	./generatorMacierzy $k $i ""$k"x"$i"A.txt"
	sleep 0.2 
	./generatorMacierzy $i $j ""$i"x"$j"B.txt"
	./mnozenieMacierzy ""$k"x"$i"A.txt" ""$i"x"$j"B.txt"  ""$k"x"$j"C.txt"
	./ompMnozenieMacierzy ""$k"x"$i"A.txt" ""$i"x"$j"B.txt"  ""$k"x"$j"C.txt"
	let k=$k+512
	let j=$j+488
done