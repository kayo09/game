//Author: i hate it
//screen interface
#ifdef SCREEN_H
#define SCREEN_H

#include <stddef.h>  // for size_t if you later switch indices

#ifdef __cplusplus
extern "C" {
#endif

// ------------------------------------------------------------------
// Public constants (kept in sync with screen.c).
// If you change these in screen.c, update them here (or centralize).
// ------------------------------------------------------------------
#define SCREEN_MIN_COLS 10
#define SCREEN_MIN_ROWS 5
#define SCREEN_MAX_COLS 1000
#define SCREEN_MAX_ROWS 500

// ------------------------------------------------------------------
// Global terminal geometry (currently set in main()).
// Prefer providing getters/setters instead of exposing globals;
// for now we mirror your implementation.
// ------------------------------------------------------------------
extern int term_rows;
extern int term_cols;

// ------------------------------------------------------------------
// Screen state
// Note: making the struct public because screen.c manipulates fields
// directly. If you want an opaque type later, move this definition
// into screen.c and add accessor functions.
// ------------------------------------------------------------------
typedef struct {
    int frame0;
    int frame1;
    char status[4];      
    char **frame_buffer; // rows x cols buffer allocated by init
} ScreenState;

// ------------------------------------------------------------------
// Lifecycle
// rows/cols must be validated by caller before calling init.
// Returns NULL on failure (errno set by perror in implementation).
// ------------------------------------------------------------------
ScreenState* init_screen_state(int rows, int cols);

// Frees all allocations inside ScreenState and the struct itself.
// NOTE: Matches current implementation, which requires rows.
// Consider refactoring to store rows/cols in ScreenState so this
// can just be free_screen_state(ScreenState* state).
void free_screen_state(ScreenState* state, int rows);

// ------------------------------------------------------------------
// Rendering
// Draws a single frame using global term_rows/term_cols for size
// and writes characters into state's frame_buffer.
// ------------------------------------------------------------------
void frame(ScreenState* state);

#ifdef __cplusplus
} // extern "C"
#endif
//see: kayparmar[!=].com