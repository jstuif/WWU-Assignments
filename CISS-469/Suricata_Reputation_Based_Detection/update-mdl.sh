#!/usr/bin/env bash

#Joshua Stuifbergen
#2/2/2020
#CISS469
#Reputation-Based Detection using Suricata

touch mdl.list

#input1="./ip.txt"
wget -q "https://gitlab.cs.wwu.edu/tsikerm/assignment-files/raw/master/mdl.csv"
input2="./mdl.csv"
input3="./ip2.txt"
array2=() #IPs from mdl.csv file
array3=() #Both IPs and there counts pair in an element
array4=() #Count and IP on seperate lines


#grabs each CSV line, cuts non-relative data, greps for an IP, and stores as an element
mapfile -t array2 < <(cut -d, -f3 $input2 | grep -E -o "([0-9]{1,3}[\.]){3}[0-9]{1,3}")


#Removed IP 127.0.0.1
arrayExcLocal=()
for i in ${array2[@]}; do
	[[ $i != 127.0.0.1 ]] && arrayExcLocal+=($i)
done
array2=(${arrayExcLocal[@]})

#Transfers array elemetents to newlines in file so it can later be sorted.
printf "%s\n" ${array2[@]} > ip2.txt

#Sorts the IPs, counts the unique occurence of the strings, and prints the high number top down
mapfile -t array3 < <(sort $input3 | uniq -c)

printf "%s\n" ${array3[@]} > ipAndCount.txt

#Seperate the element by Count and IP on new lines in the file ipAndCount
read -ra array4 -d '' < ipAndCount.txt

> "mdl.list"

tP=1.5
echo tP: $tP
dog=64.0
cat=127.0
for (( i = 0 ; i <= ${#array4[@]} ; i+=2 )); do
	j=$(($i + 1))
		tempRepScore=$(bc -l <<< ${array4[$i]}*$tP)
		echo tempRepScore $tempRepScore
		if [[ $(echo "$tempRepScore > $dog" | bc -l) -eq 1 ]] && [[ $(echo "$tempRepScore < $cat" | bc -l) -eq 1 ]]; then
			category=1
			repScore=$tempRepScore
			echo FIRST
			echo REP:first $repScore
		elif [[ $(echo "$tempRepScore > $cat" | bc -l) -eq 1 ]]; then
				category=1
				repScore=127
				echo SECOND
			elif [[ $(echo "$tempRepScore == $tP" | bc -l) -eq 1 ]]; then
				category=1
				repScore=1
				echo THIRD
					else
							category=1
							repScore=$tempRepScore
				echo FOURTH
		fi
	IP=(${array4[$j]})
	echo "$IP","$category","$repScore" >> mdl.list
	 j=$(($j + 2))
done

#Deletes extra line from above
sed -i '$d' "mdl.list"

rm ./mdl.csv

#Sources
#Grep for IP
#https://www.shellhacks.com/regex-find-ip-addresses-file-grep/
#For (sort -n -t. -k1,1 -k2,2 -k3,3 -k4,4 $input3 | uniq -c | sort -n -r -s)
#https://unix.stackexchange.com/questions/246104/unix-count-unique-ip-addresses-sort-them-by-most-frequent-and-also-sort-them
#How to get a float
#https://unix.stackexchange.com/questions/40786/how-to-do-integer-float-calculations-in-bash-or-other-languages-frameworks
#Removing a single element from an array1
#https://stackoverflow.com/questions/16860877/remove-an-element-from-a-bash-array
