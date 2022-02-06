#! /bin/bash
declare -a Size=(1024)
mkdir -p Output
for i in "${Size[@]}"
	do
	./batch 2>&1 | tee ./Output/${i}_log.dat
