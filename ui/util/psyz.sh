# nonono. util/psyz.sh
#!/bin/sh
export COLS=$(tput cols)
export ROWS=$(tput lines)

echo "[DEBUG:]Terminal is ${COLS}x${ROWS}"
