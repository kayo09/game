//Author: i hate it
//c.screen
//supplementry: https://cplusplus.com/reference/cstdio/printf/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
int term_rows=0;
int term_cols=0;

void frame(){
//    clock_t start_t; add clock safeguard after tests
//    start_t = clock();
    
    // Validate dimensions
    if(term_cols <= 0 || term_rows <= 0 || term_cols > 200 || term_rows > 100) {
        printf("Invalid dimensions for frame: %dx%d\n", term_cols, term_rows);
        return;
    }
    
    printf("\nDrawing frame with dimensions %dx%d:\n", term_cols, term_rows);
    
    // Draw the frame
    for(int row = 0; row < term_rows; row++) {
        for(int col = 0; col < term_cols; col++) {
            if(row == 0 || row == term_rows-1) {
                // Top and bottom borders use -
                printf("-");
            } else if(col == 0 || col == term_cols-1) {
                // Left and right borders use |
                printf("|");
            } else {
                // Inside the frame is empty space
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(){
    // Run the shell script to get terminal dimensions
    system("./util/psyz.sh");
    
    // Open the file created by the shell script
    FILE *f = fopen("rowcol.txt", "r");
    if(!f) {
        perror("fopen");
        return 1;
    }
    
    char buffer[256];

    if(fgets(buffer, sizeof(buffer), f)!=NULL){
        if (sscanf(buffer, "%d CR %d", &term_cols, &term_rows)==2){
            if(term_cols<=0 || term_rows<=0 || term_cols >1000 || term_rows > 1000){
                fprintf(stderr, "Invalid terminal dimensions: %dx%d\n", term_cols, term_rows);
                fclose(f);
                return 1;
            }
            printf("[DEBUG:]Successfully read dimensions: %d columns x %d rows\n", term_cols, term_rows);
            
            // Draw the frame using the global variables
            frame();
            
        } else {
            fprintf(stderr, "Error parsing dimensions from rowcol.txt\n");
        }
    }
    fclose(f);
    return 0;
}
// int main(){
//     // Run the shell script to get terminal dimensions
//     system("./util/psyz.sh");
    
//     // Open the file created by the shell script
//     FILE *f = fopen("rowcol.txt", "r");
//     if(!f) {
//         perror("fopen");
//         return 1;
//     }
    
//     char buffer[256];
//     int term_cols = 0, term_rows = 0;

//     if(fgets(buffer, sizeof(buffer), f)!=NULL){
//         if (sscanf(buffer, "%d CR %d", &term_cols, &term_rows)==2){
//             if(term_cols<=0 || term_rows<=0 || term_cols >1000 || term_rows > 1000){
//                 fprintf(stderr, "Invalid terminal dimensions: %dx%d\n", term_cols, term_rows);
//                 fclose(f);
//                 return 1;
//             }
//             printf("[DEBUG:]Successfully read dimensions: %d columns x %d term_rows\n", term_cols, term_rows);
//             if(term_cols <=200 ){
//                 for (int i =0; i<term_cols; i++) printf("-");
//                 printf("\n");
//             } else {
//                 printf("Terminal too wide for border display\n");
//             }
//         } else {
//             fprintf(stderr, "Error parsing dimensions from rowcol.txt\nreport @ github.com/kayo09/game");
//         }
//     }
//     fclose(f);
//     return 0;
// }