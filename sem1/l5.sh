#!/bin/bash

echo "Путь: "
read path

path2=${path//'/'/'.'}
if  [ -d "$path" ] ;
then
    data=`date +%Y-%m-%d`
    echo $path2 >"$path"/"$data".txt
else
    echo "Заданной папки нет, создать ее Y/n?"
    read answer
    if  [ $answer == "Y" ] ; then
    echo $answer
    mkdir "$path"
elif  [ $answer == "n" ] ; then
    echo n
else
    echo неверный ввод
fi
fi



read -p "Press enter to continue..."