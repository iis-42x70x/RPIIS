#!/bin/bash

if [ ! -n "$1" ]; then
echo "No parameters found. "
exit 1
fi

if [ ! -n "$2" ]; then
echo "No parameters found. "
exit 1
fi

source=$1
destination=$2
echo $source
echo $destination

if [ ! -d source ]; then
    echo "Директория-источник $source не существует."
    exit 1
fi

if [ ! -d destination ]; then
    echo "Директория-назначение $destination не существует."
    exit 1
fi

cd destination

for file in *; do
    filename=$(basename "$file")
    echo $filename
    cd -
    cd source
    if [ ! -f $filename ] ; then
        echo "Копируем $filename из $destination в $source"
        cp $destination/$filename $source/$filename
    fi
    cd -
    cd destination
done

cd -
cd source

for file in *; do
    filename=$(basename "$file")
    echo $filename
    cd -
    cd destination
    if [ ! -f $filename ] ; then
        echo "Удаляем $filename из $source"
        cd -
        cd source
        rm $file
    fi
done

echo "Синхронизация завершена."