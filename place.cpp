#define GL_SILENCE_DEPRECATION

// #include <GL/freeglut.h>
#include <GL/gl.h>
#include <cstdio>
#include "draw.cpp"

void placeApple() {
    bool applePlaced = false;
    while (!applePlaced) {
        appleX = (rand() % ((boundaryRight - snakeSize) / snakeSize)) * snakeSize;
        appleY = (rand() % ((boundaryTop - snakeSize) / snakeSize)) * snakeSize;
        while (appleX == bombX && appleY == bombY) {
            //make sure the apple cannot overlap with the bomb
            appleX = (rand() % ((boundaryRight - snakeSize) / snakeSize)) * snakeSize;
            appleY = (rand() % ((boundaryTop - snakeSize) / snakeSize)) * snakeSize;
        }
        applePlaced = true;
        for (int i = 0; i < snakeLength; i++) {
            if (appleX == snakeX[i] && appleY == snakeY[i]) {
                applePlaced = false;
                break;
            }
        }
    }
}

void placeGoldenApple() {
    bool goldenApplePlaced = false;
    while (!goldenApplePlaced) {
        goldenAppleX = (rand() % ((boundaryRight - snakeSize) / snakeSize)) * snakeSize;
        goldenAppleY = (rand() % ((boundaryTop - snakeSize) / snakeSize)) * snakeSize;

        // Ensure golden apple doesn't overlap with the bomb or normal apple
        if ((goldenAppleX == bombX && goldenAppleY == bombY) || 
            (goldenAppleX == appleX && goldenAppleY == appleY)) {
            continue; // Skip the rest of the loop and try again
        }

        goldenApplePlaced = true;
        for (int i = 0; i < snakeLength; i++) {
            if (goldenAppleX == snakeX[i] && goldenAppleY == snakeY[i]) {
                goldenApplePlaced = false; // It's on the snake, try again
                break;
            }
        }
    }
}


// Function to place the bomb at a random location
void placeBomb() {
    // Random position for bomb
    bombX = (rand() % ((boundaryRight - snakeSize) / snakeSize)) * snakeSize;
    bombY = (rand() % ((boundaryTop - snakeSize) / snakeSize)) * snakeSize;
    bombTicks = 0; // Reset ticks
    bombTickTimer = 0; // Reset bomb tick timer


}
