#define GL_SILENCE_DEPRECATION

// #include <GL/freeglut.h>    //remove this for csil
#include <GL/gl.h>
#include <cstdio>
#include "game.cpp"

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(width, height);
    glutCreateWindow("BoaBomb");

    init(); // Ensure all initialization is done first

    loadHighScores();
    glutKeyboardFunc(keyboardRegular); // Set up keyboard input
    glutSpecialFunc(keyboard); // Set up special key input (like arrow keys)
    glutDisplayFunc(display); // Set up the display function

    if (!timerActive) {
        timerActive = true;
        glutTimerFunc(100, update, 0); // Start the timer for game updates
    }

    glutMainLoop();

    return 0;
}