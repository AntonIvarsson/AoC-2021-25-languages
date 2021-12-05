#!/bin/bash
input="input.txt"

depth=0
horizontal=0
while IFS= read -r line
do
  arrIN=(${line//\s/ })
  command=${arrIN[0]}
  amount=${arrIN[1]}
  if [ ${command} = "forward" ]
  then
    horizontal=$((horizontal+${amount}))
  fi

  if [ ${command} = "down" ]
  then
    depth=$((depth+${amount}))
  fi

  if [ ${command} = "up" ]
  then
    depth=$((depth-${amount}))
  fi

done < "$input"
echo $((${horizontal}*${depth}))

aim=0
depth=0
horizontal=0
while IFS= read -r line
do
  arrIN=(${line//\s/ })
  command=${arrIN[0]}
  amount=${arrIN[1]}
  if [ ${command} = "down" ]
  then
    aim=$((aim+${amount}))
  fi

  if [ ${command} = "up" ]
  then
    aim=$((aim-${amount}))
  fi

  if [ ${command} = "forward" ]
  then
    horizontal=$((horizontal+${amount}))
    newAim=$((${aim}*${amount}))
    depth=$((depth+${newAim}))
  fi

done < "$input"
echo $((${horizontal}*${depth}))