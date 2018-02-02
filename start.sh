#!/bin/bash
cd build

# Nom de l'algorithme
algo="random"
# Nombre d'exécutions
nbRun=5
# Nombre d'itérations
nbItr=5

# Aléatoire
echo 'Algorithm: ' $algo

# Définition des colonnes
if [ $algo == "random" ]; then
	header='fitness'
else
	header='nbItr;fitness' 
fi

# Ajout des colonnes
echo ${header} > ../output/${algo}.csv

# Éxécution de l'algorithme
for((i=1; i <= ${nbRun}; i++))
do
	echo -n $i' '
	result=$(./src/cc-simulator-main ${algo} ${nbItr})
	echo ${result} >> ../output/${algo}.csv
done

# Saut à la ligne
echo