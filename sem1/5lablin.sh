#!/bin/bash

# Проверка, что передан параметр
if [ -z "$1" ]; then
  echo "Укажите число в качестве параметра."
  exit 1
fi

# Проверка, что параметр является числом
if ! [[ "$1" =~ ^[0-9]+$ ]]; then
  echo "Параметр должен быть числом."
  exit 1
fi

DIVISOR=$1
FOUND=0

# Поиск процессов
ps -A -o pid,comm | tail -n +2 | while read -r PID COMM; do
  if (( PID % DIVISOR == 0 )); then
    echo "$COMM $PID"
    FOUND=1
  fi
done

# Если процесс не найден
if [ $FOUND -eq 0 ]; then
  echo "процесс не найден"
  sleep 3
fi
