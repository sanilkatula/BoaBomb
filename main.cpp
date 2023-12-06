#define GL_SILENCE_DEPRECATION

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cstdio>
#include "game.cpp"

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(2 | 0);
    glutInitWindowSize(width, height); // Creates the window
    glutCreateWindow("BoaBomb");
    glutKeyboardFunc(keyboardRegular);
    drawApple(); // Draw the apple
    drawBomb();


    init();




    glutSpecialFunc(keyboard); // Keeps track of keybord inputs
    glutDisplayFunc(display); // Initilizes the Objects




    if (!timerActive) {
        timerActive = true;
        glutTimerFunc(100, update, 0);
    }


    glutMainLoop();


    return 0;
}