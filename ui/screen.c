//Author: i hate it
//c.screen
#include <stdlib.h>
#include <stdio.h>

int main(){
//    system("export COLS=$(tput cols);export ROWS=$(tput lines);");
// ^^ doesn't work since a subshell spawn occurs, using util for now ^^
    system("./util/psyz.sh");
    char *row = getenv("ROWS");
    char *col = getenv("COLS");
    printf(row,col);
    return 0;
}