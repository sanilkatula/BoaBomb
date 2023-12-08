#define GL_SILENCE_DEPRECATION

// #include <GL/gl.h>
#include <cstdio>
#include <cstring>
#include "gameConstants.h"
#include "playerScore.h"
#include "globals.h"
#include <cmath>

PlayerScore highScores[MAX_SCORES]; // Definition
char playerName[50];
bool isEnteringName = false;
int nameLength = 0;

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
    // Draw apple body
    glColor3f(1.0, 0.0, 0.0); // Red color for the apple
    const float radius = snakeSize / 2.0f; // Radius of the circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(appleX + radius, appleY + radius); // Center of the circle
    for (int i = 0; i <= 360; i += 10) {
        float angle = static_cast<float>(i) * 3.14159f / 180.0f;
        glVertex2f(appleX + radius + cos(angle) * radius, appleY + radius + sin(angle) * radius);
    }
    glEnd();

    // Draw stem at the top
    glColor3f(0.55, 0.27, 0.07); // Brown color for the stem
    float stemWidth = radius / 4;
    float stemHeight = radius / 2;
    glBegin(GL_QUADS);
    glVertex2f(appleX + radius - stemWidth / 2, appleY + radius * 2);
    glVertex2f(appleX + radius + stemWidth / 2, appleY + radius * 2);
    glVertex2f(appleX + radius + stemWidth / 2, appleY + radius * 2 + stemHeight);
    glVertex2f(appleX + radius - stemWidth / 2, appleY + radius * 2 + stemHeight);
    glEnd();

    // Draw leaf near the stem
    glColor3f(0.0, 1.0, 0.0); // Green color for the leaf
    glBegin(GL_TRIANGLES);
    glVertex2f(appleX + radius + stemWidth / 2, appleY + radius * 2 + stemHeight / 2);
    glVertex2f(appleX + radius + stemWidth * 2, appleY + radius * 2 + stemHeight);
    glVertex2f(appleX + radius + stemWidth / 2, appleY + radius * 2 + stemHeight * 1.5);
    glEnd();
}



void drawGoldenApple() {
    if (goldenAppleActive) {
        // Draw golden apple body
        glColor3f(1.0, 0.84, 0.0); // Gold color for the apple
        const float radius = snakeSize / 2.0f; // Radius of the circle
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(goldenAppleX + radius, goldenAppleY + radius); // Center of the circle
        for (int i = 0; i <= 360; i += 10) {
            float angle = static_cast<float>(i) * 3.14159f / 180.0f;
            glVertex2f(goldenAppleX + radius + cos(angle) * radius, goldenAppleY + radius + sin(angle) * radius);
        }
        glEnd();

        // Draw stem at the top
        glColor3f(0.55, 0.27, 0.07); // Brown color for the stem
        float stemWidth = radius / 4;
        float stemHeight = radius / 2;
        glBegin(GL_QUADS);
        glVertex2f(goldenAppleX + radius - stemWidth / 2, goldenAppleY + radius * 2);
        glVertex2f(goldenAppleX + radius + stemWidth / 2, goldenAppleY + radius * 2);
        glVertex2f(goldenAppleX + radius + stemWidth / 2, goldenAppleY + radius * 2 + stemHeight);
        glVertex2f(goldenAppleX + radius - stemWidth / 2, goldenAppleY + radius * 2 + stemHeight);
        glEnd();

        // Draw leaf near the stem
        glColor3f(0.0, 1.0, 0.0); // Green color for the leaf
        glBegin(GL_TRIANGLES);
        glVertex2f(goldenAppleX + radius + stemWidth / 2, goldenAppleY + radius * 2 + stemHeight / 2);
        glVertex2f(goldenAppleX + radius + stemWidth * 2, goldenAppleY + radius * 2 + stemHeight);
        glVertex2f(goldenAppleX + radius + stemWidth / 2, goldenAppleY + radius * 2 + stemHeight * 1.5);
        glEnd();
    }
}



void drawBomb() {
    // Calculate color intensity based on bombTicks
    float colorIntensity = (float)bombTicks / BOMB_TICK_LIMIT;
    float blueShade = 0.5 + 0.5 * sin(colorIntensity * 2 * 3.14159f); // Fluctuating blue intensity

    // Draw bomb body (similar to apple)
    glColor3f(0.0, 0.0, blueShade); // Blue color for the bomb
    const float radius = snakeSize / 2.0f; // Radius of the bomb
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(bombX + radius, bombY + radius); // Center of the circle
    for (int i = 0; i <= 360; i += 10) {
        float angle = static_cast<float>(i) * 3.14159f / 180.0f;
        glVertex2f(bombX + radius + cos(angle) * radius, bombY + radius + sin(angle) * radius);
    }
    glEnd();

    // Draw fuse (white rope)
    glColor3f(1.0, 1.0, 1.0); // White color for the fuse
    float fuseWidth = radius / 8;
    float fuseHeight = radius/2;
    glBegin(GL_QUADS);
    glVertex2f(bombX + radius - fuseWidth / 2, bombY + radius * 2);
    glVertex2f(bombX + radius + fuseWidth / 2, bombY + radius * 2);
    glVertex2f(bombX + radius + fuseWidth / 2, bombY + radius * 2 + fuseHeight);
    glVertex2f(bombX + radius - fuseWidth / 2, bombY + radius * 2 + fuseHeight);
    glEnd();

    // Draw fire at the end of the fuse
    glColor3f(1.0, 0.0, 0.0); // Red color for the fire
    glBegin(GL_TRIANGLES);
    glVertex2f(bombX + radius, bombY + radius * 2 + fuseHeight);
    glVertex2f(bombX + radius - fuseWidth, bombY + radius * 2 + fuseHeight * 1.5);
    glVertex2f(bombX + radius + fuseWidth, bombY + radius * 2 + fuseHeight * 1.5);
    glEnd();

    glColor3f(1.0, 0.843, 0.0); // Orange color for the fire
    glBegin(GL_TRIANGLES);
    glVertex2f(bombX + radius, bombY + radius * 2 + fuseHeight * 1.2);
    glVertex2f(bombX + radius - fuseWidth * 0.8, bombY + radius * 2 + fuseHeight * 1.7);
    glVertex2f(bombX + radius + fuseWidth * 0.8, bombY + radius * 2 + fuseHeight * 1.7);
    glEnd();
}


void drawSnake() {
    for (int i = 0; i < snakeLength; i++) {
        // Gradient color from head to tail
        float intensity = (float)i / snakeLength;
        glColor3f(0.0, intensity, 0.0); // Gradually changing green intensity

        glBegin(GL_QUADS);
        glVertex2i(snakeX[i], snakeY[i]);
        glVertex2i(snakeX[i] + snakeSize, snakeY[i]);
        glVertex2i(snakeX[i] + snakeSize, snakeY[i] + snakeSize);
        glVertex2i(snakeX[i], snakeY[i] + snakeSize);
        glEnd();
    }

    // Draw the head with a different color
    glColor3f(0.0, 0.8, 0.8); // Different color for the head
    glBegin(GL_QUADS);
    glVertex2i(snakeX[0], snakeY[0]);
    glVertex2i(snakeX[0] + snakeSize, snakeY[0]);
    glVertex2i(snakeX[0] + snakeSize, snakeY[0] + snakeSize);
    glVertex2i(snakeX[0], snakeY[0] + snakeSize);
    glEnd();
}


void drawArrow(int x, int y, ArrowDirection direction) {
    int arrowWidth = snakeSize / 2;  // Width of the arrow body
    int arrowHeight = snakeSize;     // Length of the arrow body
    int headHeight = snakeSize / 2;  // Height of the arrow head

    glColor3f(1.0, 1.0, 1.0);  // White color

    // Draw the arrow body (rectangle)
    glBegin(GL_QUADS);
    if (direction == ARROW_LEFT || direction == ARROW_RIGHT) {
        int bodyLength = arrowHeight - headHeight;
        if (direction == ARROW_LEFT) {
            x += headHeight;  // Adjust starting x for leftward arrow
        }
        glVertex2i(x, y + snakeSize / 2 - arrowWidth / 2);
        glVertex2i(x, y + snakeSize / 2 + arrowWidth / 2);
        glVertex2i(x + bodyLength, y + snakeSize / 2 + arrowWidth / 2);
        glVertex2i(x + bodyLength, y + snakeSize / 2 - arrowWidth / 2);
    } else {  // ARROW_UP or ARROW_DOWN
        int bodyLength = arrowHeight - headHeight;
        if (direction == ARROW_UP) {
            y += headHeight;  // Adjust starting y for upward arrow
        }
        glVertex2i(x + snakeSize / 2 - arrowWidth / 2, y);
        glVertex2i(x + snakeSize / 2 + arrowWidth / 2, y);
        glVertex2i(x + snakeSize / 2 + arrowWidth / 2, y + bodyLength);
        glVertex2i(x + snakeSize / 2 - arrowWidth / 2, y + bodyLength);
    }
    glEnd();

    // Draw the arrow head (triangle)
    glBegin(GL_TRIANGLES);
    if (direction == ARROW_DOWN || direction == ARROW_UP) {
        // Both ARROW_DOWN and ARROW_UP will have a downward-pointing arrow head
        glVertex2i(x + snakeSize / 2, y + arrowHeight);  // Bottom point of the triangle
        glVertex2i(x + snakeSize / 2 - arrowWidth / 2, y + arrowHeight - headHeight);  // Top left
        glVertex2i(x + snakeSize / 2 + arrowWidth / 2, y + arrowHeight - headHeight);  // Top right
    } else if (direction == ARROW_LEFT) {
        glVertex2i(x, y + snakeSize / 2);  // Leftmost point
        glVertex2i(x + headHeight, y + snakeSize / 2 - arrowWidth / 2);  // Right top
        glVertex2i(x + headHeight, y + snakeSize / 2 + arrowWidth / 2);  // Right bottom
    } else if (direction == ARROW_RIGHT) {
        glVertex2i(x + arrowHeight, y + snakeSize / 2);  // Rightmost point
        glVertex2i(x + arrowHeight - headHeight, y + snakeSize / 2 - arrowWidth / 2);  // Left top
        glVertex2i(x + arrowHeight - headHeight, y + snakeSize / 2 + arrowWidth / 2);  // Left bottom
    }

    glEnd();
}


void drawNPC(int x, int y, ArrowDirection direction) {
    drawArrow(x, y, direction);
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

    snprintf(scoreText, sizeof(scoreText), "Score: %d", snakeLength - 1);

    // Calculate positions for the text
    int gameOverPosX = width / 2 - (strlen(gameOverText) * 9) / 2;
    int scorePosX = width / 2 - (strlen(scoreText) * 9) / 2;
    int restartPosX = width / 2 - (strlen(restartText) * 9) / 2;
    int exitPosX = width / 2 - (strlen(exitText) * 9) / 2;

    int gameOverPosY = 2*height / 3 + 60;
    int scorePosY = 2*height / 3 + 30;
    int restartPosY = 2*height / 3;
    int exitPosY = 2*height / 3 - 30;

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


void loadHighScores() {
    FILE *file = fopen("highscores.txt", "r");
    if (file != NULL) {
        fread(highScores, sizeof(PlayerScore), MAX_SCORES, file);
        fclose(file);
    }
}

void saveHighScores() {
    FILE *file = fopen("highscores.txt", "w");
    if (file != NULL) {
        fwrite(highScores, sizeof(PlayerScore), MAX_SCORES, file);
        fclose(file);
    }
}

void updateHighScores(int score) {
    int position = -1;
    for (int i = 0; i < MAX_SCORES; i++) {
        if (score > highScores[i].score) {
            position = i;
            break;
        }
    }

    // If the score is among the top 10, insert it
    if (position != -1) {
        // Shift lower scores down
        for (int i = MAX_SCORES - 1; i > position; i--) {
            highScores[i] = highScores[i - 1];
        }

        // Insert the new score at the found position
        highScores[position].score = score;
        strcpy(highScores[position].playerName, "new player");
    }
}


void initializeHighScores() {
    for (int i = 0; i < MAX_SCORES; i++) {
        highScores[i].score = 0; // Set a default score, like 0
        strcpy(highScores[i].playerName, "Empty"); // Default name
    }
}

void drawLeaderboardTitle() {
    const char* title = "Leaderboard";
    int titlePosX = width / 2 - (strlen(title) * 9) / 2;
    int titlePosY = height / 2; // Adjust this as needed

    glColor3f(1.0, 1.0, 1.0); // White color for the title
    glRasterPos2i(titlePosX, titlePosY);

    for (const char* c = title; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}

void drawHighScores() {
    char scoreText[100];
    int scoresY = 100; // Starting Y position for the scores
    int scoresX = width / 3 - 30; // X position for the scores, adjust as needed

    glColor3f(1.0, 1.0, 1.0); // Set text color

    // Draw the title
    drawLeaderboardTitle();

    // Draw top 5 scores in a single column
    for (int i = 7; i > 0; i--) { // Limit to top 5 scores
        snprintf(scoreText, sizeof(scoreText), "%d. %s: %d", i, highScores[i].playerName, highScores[i].score);
        glRasterPos2i(scoresX, scoresY);
        scoresY += 20; // Adjust for next score

        for (char* c = scoreText; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
        }
    }
}




