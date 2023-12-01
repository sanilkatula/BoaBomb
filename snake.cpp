#include <GL/freeglut.h>


const int width = 500;
const int height = 500;
// Height and Width of Window


int snakeSize = 20; // Size of each pixel on the screen
int snakeX[100], snakeY[100]; // Coordinates of the Snake
int direction = 0;  // 0: right, 1: up, 2: left, 3: down


int boxX = width - 120;  // Initial position of the npc1
int boxY = height - 120;


int box2X = width / 2 - snakeSize;  // Initial position of npc2
int box2Y = height - snakeSize;


int box3X = width - snakeSize;  // Initial position of npc3
int box3Y = height / 2 - snakeSize;


void drawSnake() {
    // Draws the box of the snake
    glColor3f(0.0, 1.0, 0.0);  // Snake color (green)
    glBegin(GL_QUADS);
    glVertex2i(snakeX[0], snakeY[0]);
    glVertex2i(snakeX[0] + snakeSize, snakeY[0]);
    glVertex2i(snakeX[0] + snakeSize, snakeY[0] + snakeSize);
    glVertex2i(snakeX[0], snakeY[0] + snakeSize);
    glEnd();
}


void drawNPC(int x, int y) {
    // Draws the box of npc at the specified x and y coordinates
    glColor3f(1.0, 1.0, 1.0);  // Box color (white)
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + snakeSize, y);
    glVertex2i(x + snakeSize, y + snakeSize);
    glVertex2i(x, y + snakeSize);
    glEnd();
}


void init() {
    //Initilizes the Display
    glClearColor(0.0, 0.0, 0.0, 1.0); // Color of the background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, width, 0, height); // Sets the window display
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clears the screen after every frame


    drawSnake();
    drawNPC(boxX, boxY);      // NPC1
    drawNPC(box2X, box2Y);    // NPC2
    drawNPC(box3X, box3Y);    // NPC3


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


void update(int) {
    //Updates each frame every 100 milliseconds using recursion
   
    glutPostRedisplay();


    // Update snake position
    switch (direction) {
        case 0:
            snakeX[0] += snakeSize;
            break;
        case 1:
            snakeY[0] += snakeSize;
            break;
        case 2:
            snakeX[0] -= snakeSize;
            break;
        case 3:
            snakeY[0] -= snakeSize;
            break;
    }


    // Update NPCs' positions
    boxX += snakeSize;
    box2X += snakeSize;
    box3X -= snakeSize;


    // Wrap NPCs to the opposite side when reaching the edges
    if (boxX >= width) {
        boxX = 0;
    }


    if (box2X >= width) {
        box2X = 0;
    }


    if (box3X < 0) {
        box3X = width - snakeSize;
    }


    // Snake boundary check
    if (snakeX[0] >= width) snakeX[0] = 0;
    if (snakeX[0] < 0) snakeX[0] = width - snakeSize;
    if (snakeY[0] >= height) snakeY[0] = 0;
    if (snakeY[0] < 0) snakeY[0] = height - snakeSize;


    glutTimerFunc(100, update, 0); // Calls update every 100 milliseconds
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(2 | 0);
    glutInitWindowSize(width, height); // Creates the window
    glutCreateWindow("Snake Game");




    init();


    glutSpecialFunc(keyboard); // Keeps track of keybord inputs
    glutDisplayFunc(display); // Initilizes the Objects
    glutTimerFunc(100, update, 0);


    glutMainLoop();


    return 0;
}





