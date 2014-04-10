#!/bin/bash

for i in $(seq -f "%03g"  0 100); do
	for j in $(seq -f "%03g"  0 100); do
		for k in $(seq -f "%03g"  0 100); do
			echo "./crot $1 $2/$i-$j-$k.png 0.$i 0.$j 0.$k;";
			./crot anin.png $i-$j-$k.png 0.$i 0.$j 0.$k;
		done
	done
done
