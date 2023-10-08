#!/bin/bash

IFS=$'\n'

tput clear

pause=0
if (( $#==0 )); then
    pause=0
else
    pause=$1
fi

j=0
cnt=0

chars=()
pos_x=()
pos_y=()

while read A; do
    for (( i=0; $i<${#A}; ((i++)) )); do
        char=${A:$i:1}
        if [[ $char != [[:space:]] ]]; then
            chars[$j]=${A:$i:1}
            pos_x[$j]=$i
            pos_y[$j]=$cnt
            ((j++))
        fi
    done
    ((cnt++))
done

#echo $cnt $j $i
#echo ${#chars[*]} ${chars[*]}
#echo ${#pos_x[*]} ${pos_x[*]}
#echo ${#pos_y[*]} ${pos_y[*]}

((j--))
perm=$(shuf -i 0-$j)
#echo "perm: " $perm

i=1
j=$((j+2))

while (( i < j )); do
    sleep $pause
    pos=$(echo ${perm[0]} | cut -d ' ' -f $i)
    tput cup ${pos_y[pos]} ${pos_x[pos]}
    echo ${chars[pos]}
    ((i++))
done

tput cup $cnt 0
