#define GL_SILENCE_DEPRECATION

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cstdio>

int appleX, appleY;
bool timerActive = false;


const int width = 500;
const int height = 500;
// Height and Width of Window


const int boundaryLeft = 0;
const int boundaryRight = width;
const int boundaryTop = height;
const int boundaryBottom = 0;



int snakeSize = 20;                     // Size of each pixel on the screen
int snakeX[100], snakeY[100];           // Coordinates of the Snake
int direction = 0;                      // 0: right, 1: up, 2: left, 3: down



int boxX = width - 120;                 // Initial position of the npc1
int boxY = height - 120;




int box2X = width / 2 - snakeSize;      // Initial position of npc2
int box2Y = height - snakeSize;




int box3X = width + snakeSize;          // Initial position of npc3
int box3Y = height / 2 - snakeSize;


int snakeLength = 1;


const int BOMB_TICK_LIMIT = 5;
const int BOMB_TICK_RATE = 1000;
int bombX, bombY;
int bombTicks = 0;
int bombTickTimer = 0;


void drawApple() {
    glColor3f(1.0, 0.0, 0.0);           // Red color for the apple
    glBegin(GL_QUADS);
    glVertex2i(appleX, appleY);
    glVertex2i(appleX + snakeSize, appleY);
    glVertex2i(appleX + snakeSize, appleY + snakeSize);
    glVertex2i(appleX, appleY + snakeSize);
    glEnd();
}


void drawBomb() {
    if (bombTicks < BOMB_TICK_LIMIT) {
        // Interpolate color from dark blue to bright blue
        float colorIntensity = (float)bombTicks / BOMB_TICK_LIMIT;
        glColor3f(0.0, 0.0, 0.5 + 0.5 * colorIntensity); // Increasing blue intensity


        glBegin(GL_QUADS);
        glVertex2i(bombX, bombY);
        glVertex2i(bombX + snakeSize, bombY);
        glVertex2i(bombX + snakeSize, bombY + snakeSize);
        glVertex2i(bombX, bombY + snakeSize);
        glEnd();
    }
}






void drawSnake() {
    glColor3f(0.0, 1.0, 0.0); // Snake color (green)
    for (int i = 0; i < snakeLength; i++) {
        glBegin(GL_QUADS);
        glVertex2i(snakeX[i], snakeY[i]);
        glVertex2i(snakeX[i] + snakeSize, snakeY[i]);
        glVertex2i(snakeX[i] + snakeSize, snakeY[i] + snakeSize);
        glVertex2i(snakeX[i], snakeY[i] + snakeSize);
        glEnd();
    }
}




void drawNPC(int x, int y) {
    // Draws the box of npc at the specified x and y coordinates
    glColor3f(1.0, 1.0, 1.0);                               // Box color (white)
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + snakeSize, y);
    glVertex2i(x + snakeSize, y + snakeSize);
    glVertex2i(x, y + snakeSize);
    glEnd();
}


void drawBoundary() {
    glColor3f(0.6f, 0.3f, 0.0f);                            // Brown color
    glLineWidth(10.0);                                      // Set the line width for the boundary


    glBegin(GL_LINE_LOOP);                                  // Using GL_LINE_LOOP to draw a continuous line
    glVertex2i(boundaryLeft, boundaryBottom);               // Bottom left corner
    glVertex2i(boundaryRight, boundaryBottom);              // Bottom right corner
    glVertex2i(boundaryRight, boundaryTop);                 // Top right corner
    glVertex2i(boundaryLeft, boundaryTop);                  // Top left corner
    glEnd();
}


void drawScore() {
    char scoreText[20]; // Buffer to hold the score text
    snprintf(scoreText, sizeof(scoreText), "Score: %d", snakeLength - 1); 

    glColor3f(1.0, 1.0, 1.0); // Set the text color (white in this case)
    glRasterPos2i(10, height - 20); // Set the position (top left corner)

    // Render each character in the string
    for (char* c = scoreText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}
