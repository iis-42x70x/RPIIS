read -p "Start" Start
read -p "End" End
(ps aux | awk -v Start=$Start -v End=$End '{if ($4 >= Start && $4 <= End) print substr($11,2), $4}' | sed 's/]//g' | sort) > sh.txt