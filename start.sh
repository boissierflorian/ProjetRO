#!/bin/bash
cd build

if [ $# != 1 ]; then
   echo "Usage: ./start.sh <random/randomWalk>";
   exit
fi

# Nom de l'algorithme
algo=$1
# Nombre d'exécutions
nbRun=5
# Nombre d'itérations
nbEvalList="10 50 100"

# Aléatoire
echo 'Algorithm: ' $algo

# Définition des colonnes
header='nbItr;fitness'

# Ajout des colonnes
echo ${header} > ../output/${algo}.csv

# Éxécution de l'algorithme
for nbIter in ${nbEvalList}
do
	echo nbEval ${nbIter}
	for((i=1; i <= ${nbRun}; i++))
	do
		echo -n $i' '
		result=$(./src/cc-simulator-main ${algo} ${nbIter})
		echo ${result} >> ../output/${algo}.csv
	done
done
# Saut à la ligne
echo