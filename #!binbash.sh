#!/bin/bash

if [ -z "$1" ]; then
    echo "Please specify the PID of the process."
    exit 1
fi

PID=$1

# Checking whether the process is running
if ps -p $PID > /dev/null; then
    echo "Information about the process with PID $PID:"
    ps -p $PID -o pid,comm,user
else
    echo "Process with PID $PID not found."
    exit 1
fi

while true; do
    read -p "Do you want to kill the process? [Y/n]: " choice
    case "$choice" in
        [Yy]* )
            if kill -9 $PID; then
                echo "The process has been terminated."
            else
                echo "Failed to terminate the process."
            fi
            exit 0
            ;;
        [Nn]* )
            exit 0
            ;;
        * )
            echo "Incorrect input. Please enter Y or n."
            ;;
    esac
done