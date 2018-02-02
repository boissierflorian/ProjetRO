#!/bin/bash
cd build

# Nombre d'exécutions
nbRun=5
# Nombre d'itérations
nbItr=5

# Aléatoire
echo random
> ../output/random.csv
for((i=1; i <= ${nbRun}; i++))
do
	echo -n $i' '
	result=$(./src/cc-simulator-main ${nbItr})
	echo $i':'${result} >> ../output/random.csv
done
echo