#! /bin/bash



nbCol=5
aff=0
for (( exo=1; exo <=6; exo+=1)); do 
	if [[ $exo -eq 4 ]] ; then 
		continue 
	fi
	if [[ -f resultats$exo.txt ]]; then
		rm -f Resultats/resultats$exo.txt
	fi


	for (( taille=5; taille <= 100; taille+=5)); do
		echo  "-----------------------------------"
		echo -e "Taille\tDiff\tChangement\t\t\tTemps (s)"
		echo  "-----------------------------------"
		for (( diff=0; diff <= 100; diff+=20)); do
			graine=$RANDOM
			echo -ne "$taille\t$diff\t"
			./Flood-It $taille $nbCol $diff $graine $exo $aff
		done
	done >> Resultats/resultats$exo.txt
done
