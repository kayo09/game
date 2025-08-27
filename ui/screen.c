//Author: i hate it
//c.screen: current implementation creates a frame without a state
//supplementry: https://cplusplus.com/reference/cstdio/printf/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "screen.h"

int term_rows=0;
int term_cols=0;

ScreenState* init_screen_state(int rows, int cols){
    ScreenState* state = (ScreenState*)malloc(sizeof(ScreenState));
    if (!state){
        perror("Failed to allocate Screenstate");
        return NULL;
    }
    state->frame0 = 0;
    state->frame1 = 0;
    strcpy(state->status, "OK");

    // Frame buffer allocation
    state->frame_buffer = (char**)malloc(rows*sizeof(char*));
    if(!state->frame_buffer){
        perror("Failed to allocate frame buffer");
        free(state);
        return NULL;
    }
        for (int i = 0; i < rows; i++) {
        state->frame_buffer[i] = (char*)malloc(cols * sizeof(char));
        if (!state->frame_buffer[i]) {
            perror("Failed to allocate frame buffer row");
            // Clean up previously allocated rows
            for (int j = 0; j < i; j++) {
                free(state->frame_buffer[j]);
            }
            free(state->frame_buffer);
            free(state);
            return NULL;
        }
    }
    return state;
}

// Free ScreenState
void free_screen_state(ScreenState* state, int rows){
    if(state){
        for(int i = 0; i<rows; i++){
            free(state->frame_buffer[i]);
        }
        free(state->frame_buffer);
        free(state);
    }
}

void frame(ScreenState* state){
//    clock_t start_t; add clock safeguard after tests
//    start_t = clock();

    if (term_cols < SCREEN_MIN_COLS || term_rows < SCREEN_MIN_ROWS) {
        printf("Terminal too small for game UI: %dx%d (minimum: %dx%d)\n",
               term_cols, term_rows, SCREEN_MIN_COLS, SCREEN_MIN_ROWS);
        return;
    }
    if (term_cols > SCREEN_MAX_COLS || term_rows > SCREEN_MAX_ROWS) {
        printf("Terminal dimensions exceed maximum: %dx%d (maximum: %dx%d)\n",
               term_cols, term_rows, SCREEN_MAX_COLS, SCREEN_MAX_ROWS);
        return;
    }
    
    printf("\nDrawing frame with dimensions %dx%d:\n", term_cols, term_rows);
       // Store the frame in state buffer
    for (int row = 0; row < term_rows; row++) {
        for (int col = 0; col < term_cols; col++) {
            if (row == 0 || row == term_rows-1) {
                // Top and bottom borders use .
                state->frame_buffer[row][col] = '.';
            } else if (col == 0 || col == term_cols-1) {
                // Left and right borders use .
                state->frame_buffer[row][col] = '.';
            } else {
                // Inside the frame is empty space
                state->frame_buffer[row][col] = ' ';
            }
            // Print the frame as it's being stored
            printf("%c", state->frame_buffer[row][col]);
        }
        printf("\n");
    }
    
    state->frame0++;
    strcpy(state->status, "OK");
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
            // Use consistent validation limits with frame() function
            if (term_cols < SCREEN_MIN_COLS || term_rows < SCREEN_MIN_ROWS ||
                term_cols > SCREEN_MAX_COLS || term_rows > SCREEN_MAX_ROWS) {
                fprintf(stderr, "Terminal dimensions out of range: %dx%d (valid range: %dx%d to %dx%d)\n",
                        term_cols, term_rows, SCREEN_MIN_COLS, SCREEN_MIN_ROWS, SCREEN_MAX_COLS, SCREEN_MAX_ROWS);
                fclose(f);
                return 1;
            }

            printf("[DEBUG:]Successfully read dimensions: %d columns x %d rows\n", term_cols, term_rows);
            
            // Initialize ScreenState
            ScreenState* state = init_screen_state(term_rows, term_cols);
            if (!state) {
                fprintf(stderr, "Failed to initialize screen state\n");
                fclose(f);
                return 1;
            }
            // Draw the frame using the global variables
            frame(state);
           free_screen_state(state, term_rows);
        } else {
            fprintf(stderr, "Error parsing dimensions from rowcol.txt\n");
        }
    }
    fclose(f);
    return 0;
}
//see: kayparmar[!=].com