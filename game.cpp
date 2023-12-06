#define GL_SILENCE_DEPRECATION

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cstdio>
#include "draw.cpp"

void update(int value);

void init() {


    appleX = (width / 2) - (snakeSize / 2);     // Centered horizontally
    appleY = 5*snakeSize;                       // One segment above the bottom
   
    glClearColor(0.0, 0.0, 0.0, 1.0);           // Color of the background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, width, 0, height);            // Sets the window display
}




void display() {
    glClear(GL_COLOR_BUFFER_BIT);               // Clears the screen after every frame


    drawSnake();
    drawNPC(boxX, boxY);      // NPC1
    drawNPC(box2X, box2Y);    // NPC2
    drawNPC(box3X, box3Y);    // NPC3
    drawBoundary(); // Draw the boundary
    drawApple();
    drawBomb(); // Draw the bomb
    drawScore();

    glutSwapBuffers(); // Swaps the background to the back and the moving objects to the front
}




void keyboard(int key, int, int) {
    // Moves the snake
    switch (key) {
        case GLUT_KEY_UP:
            if (direction != 3)
                direction = 1;
            break;
        case GLUT_KEY_DOWN:
            if (direction != 1)
                direction = 3;
            break;
        case GLUT_KEY_LEFT:
            if (direction != 0)
                direction = 2;
            break;
        case GLUT_KEY_RIGHT:
            if (direction != 2)
                direction = 0;
            break;
    }
}




bool checkCollision(int x1, int y1, int size1, int x2, int y2, int size2) {
    return x1 < x2 + size2 &&
           x1 + size1 > x2 &&
           y1 < y2 + size2 &&
           y1 + size1 > y2;
}


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


// Function to place the bomb at a random location
void placeBomb() {
    // Random position for bomb
    bombX = (rand() % ((boundaryRight - snakeSize) / snakeSize)) * snakeSize;
    bombY = (rand() % ((boundaryTop - snakeSize) / snakeSize)) * snakeSize;
    bombTicks = 0; // Reset ticks
    bombTickTimer = 0; // Reset bomb tick timer


}


bool checkBombCollision() {
    if (bombTicks < BOMB_TICK_LIMIT) {
        return checkCollision(snakeX[0], snakeY[0], snakeSize, bombX, bombY, snakeSize);
    }
    return false;
}


bool isGameOver = false;
void resetGame() {
    snakeLength = 1;
    snakeX[0] = 100; // Reset snake's initial position
    snakeY[0] = 100;
    direction = 0; // Initial direction


    placeApple(); // Place a new apple


    // Restart the game loop
    isGameOver = false;


    if (!timerActive) {
        timerActive = true;
        glutTimerFunc(100, update, 0);
    }


    glutPostRedisplay();
}


void update(int) {
    timerActive = false;
    if (isGameOver) {
        glutPostRedisplay();
        return;
    }


    // Move the snake's body
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }


    // Update snake head position based on direction
    switch (direction) {
        case 0: // Moving right
            snakeX[0] += snakeSize;
            break;
        case 1: // Moving up
            snakeY[0] += snakeSize;
            break;
        case 2: // Moving left
            snakeX[0] -= snakeSize;
            break;
        case 3: // Moving down
            snakeY[0] -= snakeSize;
            break;
    }


    // Check for collision with the snake's own body
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            isGameOver = true;
            return;
        }
    }


    // Increment bomb tick timer
    bombTickTimer += 100; // Assuming update is called every 100 milliseconds
    if (bombTickTimer >= BOMB_TICK_RATE) {
        bombTicks++;
        bombTickTimer = 0; // Reset bomb tick timer


        if (bombTicks >= BOMB_TICK_LIMIT) {
            placeBomb(); // Place the bomb at a new location
        }
    }


    // Check for boundary collision
    if (snakeX[0] >= boundaryRight || snakeX[0] < boundaryLeft ||
        snakeY[0] >= boundaryTop || snakeY[0] < boundaryBottom) {
        isGameOver = true;
    }


    // Check for collision with the apple
    if (snakeX[0] == appleX && snakeY[0] == appleY) {
        snakeLength++; // Increase the length of the snake
        placeApple(); // Place a new apple
    }


    // Check for collisions with NPCs
    if (checkCollision(snakeX[0], snakeY[0], snakeSize, boxX, boxY, snakeSize) ||
        checkCollision(snakeX[0], snakeY[0], snakeSize, box2X, box2Y, snakeSize) ||
        checkCollision(snakeX[0], snakeY[0], snakeSize, box3X, box3Y, snakeSize)) {
        isGameOver = true;
        return; // Stop updating if a collision is detected
    }


    // Check for collisions with Bombs
    if (checkBombCollision()) {
        isGameOver = true;
        return; // Stop updating if a collision is detected
    }


    // Update NPCs' positions
    boxX += snakeSize/5;
    box2X -= snakeSize/4;
    box3Y -= snakeSize/3;


    // Wrap NPCs to the opposite side when reaching the edges
    if (boxX >= width) {
        boxX = 0;
        boxY = (rand() % ((boundaryRight - snakeSize) / snakeSize)) * snakeSize;
    }


    if (box2X <= 0) {
        box2X = width;
        boxY = (rand() % ((boundaryRight - snakeSize) / snakeSize)) * snakeSize;
    }


    if (box3Y < 0) {
        box3X = (rand() % ((boundaryRight - snakeSize) / snakeSize)) * snakeSize;
        box3Y = width - snakeSize;
    }



    glutPostRedisplay();
    if (!timerActive) {
        timerActive = true;
        glutTimerFunc(100, update, 0);
    }
}






//for easily operation of the game
void keyboardRegular(unsigned char key, int x, int y) {
    if (key == 27) { // ESC key
        exit(0);
    } else if (key == 'r' || key == 'R') {
        resetGame(); // Restart the game when 'R' is pressed
    }
}




