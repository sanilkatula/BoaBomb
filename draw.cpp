#define GL_SILENCE_DEPRECATION

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cstdio>
#include <cstring>

int appleX, appleY;
bool timerActive = false;

int normalApplesEaten = 0;
int goldenAppleX, goldenAppleY;
bool goldenAppleActive = false;
const int GOLDEN_APPLE_FREQUENCY = 10; 

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


void drawGoldenApple() {
    if (goldenAppleActive) {
        // Set color to gold
        glColor3f(1.0, 0.84, 0.0); // RGB for gold
        glBegin(GL_QUADS);
        glVertex2i(goldenAppleX, goldenAppleY);
        glVertex2i(goldenAppleX + snakeSize, goldenAppleY);
        glVertex2i(goldenAppleX + snakeSize, goldenAppleY + snakeSize);
        glVertex2i(goldenAppleX, goldenAppleY + snakeSize);
        glEnd();
    }
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

void drawMenu() {
    const char* gameTitle = "BoaBomb";
    const char* startPrompt = "Press Enter to Start the Game";
    const char* instructions[] = {
        "Avoid Bombs: They change locations and are ",
        "deadly.",
        "Beware of Arrows: If they touch the snake's head,", 
        "it's game over.",
        "Eat Apples: Increase your score.",
        "Move: Use arrow keys to control the snake."
    };

    // Calculate positions for the texts
    int titlePosX = width / 2 - (strlen(gameTitle) * 9) / 2;
    int titlePosY = height / 2 + 100;

    int promptPosX = width / 2 - (strlen(startPrompt) * 9) / 2;
    int promptPosY = height / 2 + 70;

    int leftAlignPosX = 50; // Adjust as needed, represents left margin
    int instructionStartPosY = height / 2 + 20; // Starting position for instructions
    int lineSpacing = 15; // Vertical space between lines


    glColor3f(1.0, 1.0, 1.0); // White color for texts

    // Render the game title
    glRasterPos2i(titlePosX, titlePosY);
    for (const char* c = gameTitle; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }

    // Render the start prompt
    glRasterPos2i(promptPosX, promptPosY);
    for (const char* c = startPrompt; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }

    // Render the instructions
    int instructionPosY = instructionStartPosY;
    int numInstructions = sizeof(instructions) / sizeof(instructions[0]); // Get the number of instructions

    for (int i = 0; i < numInstructions; i++) {
        glRasterPos2i(leftAlignPosX, instructionPosY);
        for (const char* c = instructions[i]; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
        }
        instructionPosY -= lineSpacing; // Move up for the next line
    }
}

void drawGameOverScreen() {
    const char* gameOverText = "Game Over";
    char scoreText[20];
    const char* restartText = "To Restart, Press R";
    const char* exitText = "To Exit, Press ESC";

    snprintf(scoreText, sizeof(scoreText), "Final Score: %d", snakeLength - 1);

    // Calculate positions for the text
    int gameOverPosX = width / 2 - (strlen(gameOverText) * 9) / 2;
    int scorePosX = width / 2 - (strlen(scoreText) * 9) / 2;
    int restartPosX = width / 2 - (strlen(restartText) * 9) / 2;
    int exitPosX = width / 2 - (strlen(exitText) * 9) / 2;

    int gameOverPosY = height / 2 + 60;
    int scorePosY = height / 2 + 30;
    int restartPosY = height / 2;
    int exitPosY = height / 2 - 30;

    // Set colors and draw each line of text
    glColor3f(1.0, 0.0, 0.0); // Red color for "Game Over"
    glRasterPos2i(gameOverPosX, gameOverPosY);
    for (const char* c = gameOverText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }

    glColor3f(1.0, 1.0, 1.0); // White color for other texts
    glRasterPos2i(scorePosX, scorePosY);
    for (const char* c = scoreText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }

    glRasterPos2i(restartPosX, restartPosY);
    for (const char* c = restartText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }

    glRasterPos2i(exitPosX, exitPosY);
    for (const char* c = exitText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}
