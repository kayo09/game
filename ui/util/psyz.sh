#! /bin/sh
COLS=$(tput cols)
ROWS=$(tput lines)

# echo "{\n\"COLS\": $COLS,\n\"ROWS\": $ROWS\n}" > rowcol.json
echo $COLS CR $ROWS > rowcol.txt
echo "[DEBUG:]Terminal is $COLS x $ROWS"
