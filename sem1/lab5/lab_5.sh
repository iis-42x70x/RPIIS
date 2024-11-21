#!/bin/bash

if [ -z "$1" ]; then
    echo "Параметр не передан"
    exit 1
fi
if ! [ -d $1 ]; then
    echo "Данной папки нет"
    exit 1
else
    ps -eo pid,etime,comm --sort=-etime | while read -r pid etime comm; do
        IFS=- read -ra time_p <<< "$etime"
        if [[ ${#time_p[@]} -gt 1 ]]; then
            etime=${time_p[1]}
            days=${time_p[0]}
        else
            days=0
            etime=${time_p}
        fi

        IFS=: read -ra time_parts <<< "$etime"
        seconds=0
        if [[ ${#time_parts[@]} -eq 3 ]]; then
            seconds=$((10#${time_parts[0]}*3600+10#${time_parts[1]}*60+10#${time_parts[2]}))
        elif [[ ${#time_parts[@]} -eq 2 ]]; then
            seconds=$((10#${time_parts[0]}*60+10#${time_parts[1]}))
        elif [[ ${#time_parts[@]} -eq 1 ]]; then
            seconds=${time_parts[0]}
        fi

        seconds=$((seconds+days*86400))
        if [[ $seconds -gt 600 ]]; then
            echo "$pid $comm $etime"
        fi
    done > result.txt
fi
exit 0