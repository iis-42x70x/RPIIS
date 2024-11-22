#usr/bin/bash

num=$1

if [ $num -lt 0 ]; then
  echo $(date +"%m-%d-%Y")
elif [ $(( $num % 2 )) -eq 0 ]; then
  echo $(date +"%m/%d/%Y")
else
  echo $(date +"%m")
fi
