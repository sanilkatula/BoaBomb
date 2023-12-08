// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

#include "playerScore.h" // Include the PlayerScore struct definition

#define MAX_SCORES 7
extern PlayerScore highScores[MAX_SCORES]; // Global declaration

typedef enum {
    ARROW_UP,
    ARROW_DOWN,
    ARROW_LEFT,
    ARROW_RIGHT
} ArrowDirection;


#endif // GLOBALS_H
