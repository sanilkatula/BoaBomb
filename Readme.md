Boa Bomb

Welcome to Boa Bomb, an exciting twist on the classic snake game. In this game, you navigate a snake through a field, collecting apples and special items, while avoiding dangerous obstacles. Get ready for an engaging gameplay experience with enhanced features and challenges!

Getting Started

Prerequisites
Ensure you have a suitable C++ compiler installed on your system to compile the game.
Clone or download this repository to your local machine.

Installation
Open your terminal or command prompt.
Navigate to the directory where you have cloned or downloaded the game files.

Compile the game by typing:
make
=======
# Welcome To BoaBomb !!! #

## Game Concept Description: ##

### Real-Time Excitement ###
As you progress, feel the excitement of real-time gameplay that never stops. Get ready for an exhilarating journey that will push your abilities to the maximum.

### Diverse Challenges ###
Travel through a lively, action-packed universe. Discover further autonomous snakes, ringing time bombs, and alluring apples that are just begging to be picked. In this complex game, every action matters.

### Arcade-Style Thrills: ###
Dive into an arcade-style encounter that combines easy controls with quick action. BoaBomb provides an engaging gaming experience that's simple to get into but challenging to master, leaving you wanting more.

### Engaging and Challenging: ###
As you navigate a number of obstacles, test your reflexes and strategic thinking. BoaBomb is made to enthrall players with its captivating dynamics, providing a great fusion of challenge and enjoyment.

#### _Come along on the thrilling journey of BoaBomb, where there will be surprises around every corner. Do you feel up to the challenge?_ ####

## How To Play: Instructions ## 

* Start: Press Enter to begin the game.
* Move: Use arrow keys to control the snake's direction.
* Restart: Press 'R' to restart the game when in the Game Over screen.
* Exit: Press ESC to exit the game.

## Game Features/Elements ## 

1. Snake: Control the green snake and guide it through the maze.
2. Apples: Collect red apples to increase your score.
3. Golden Apple: Appears after eating a certain number of normal apples. Eating it increases the snake's length significantly.
4. Bombs: Avoid bombs; they change locations and are deadly.
5. NPCs (Non-Playable Characters): Beware of arrows; if they touch the snake's head, it's game over.

## Display ##

### Main Menu ###
- Displays the game title, start prompt, and instructions.
- Press Enter to start the game.

### In-Game Screen ###
- Control the snake using arrow keys.
- Avoid bombs and arrows.
- Collect apples to increase your score.

### Game-over Screen ###
- Displays "Game Over" along with your final score.
- Press 'R' to restart or ESC to exit.

## Compilation and Execution ##

**Prerequisites**:
Ensure you have a suitable C++ compiler installed on your system to compile the game.

**Installation**:
1. Clone or download this repository to your local machine.
2. Open your terminal or command prompt.
3. Navigate to the directory where you have cloned or downloaded the game files.

**Compile and Run**:
* There needs to be an OpenGL library installed on the local computer
* Compile the code using a C++ compiler (For CSIL)
  * _clang++ main.cpp -o play -lGL -lGLU -lglut_
* Compile the game by typing (For MacOS)
  * _make_
* After successful compilation, start the game by entering:
  * _./play_

## Structure of Programming Files ##

1. Header Files
 * gameConstants.h
 * globals.h
 * playerScore.h

2. Source Files
 * draw.cpp
 * game.cpp
 * place.cpp
 * main.cpp

## draw.cpp ## 

* ```drawApple():``` </br>
Draws a red apple at the specified coordinates.

* ```drawGoldenApple():``` </br>
Draws a golden apple at the specified coordinates if it is active.

* ```drawBomb():``` </br>
Draws a bomb at the specified coordinates with a color that changes based on the bomb's tick limit.

* ```drawSnake():``` </br>
Draws the snake's body using green squares.

* ```drawNPC(int x, int y):``` </br>
Draws a non-playable character (NPC) represented by a white square at the specified coordinates (x, y).

* ```drawBoundary():``` </br>
Draws the boundary of the game area as a brown rectangle.

* ```drawScore():``` </br>
Displays the player's score at the top left corner of the window.

* ```drawMenu():``` </br>
Displays the game title, start prompt, and instructions on the menu screen.

* ```drawGameOverScreen():``` </br>
Displays the "Game Over" screen, including the final score and options to restart or exit.

## game.cpp ##

* ```init():``` </br>
Initializes the game state, setting the initial positions of the apple, snake, and other variables. Also, sets the background color.

* ```display():``` </br>
Renders the game screen based on the current game state, drawing elements such as the snake, NPCs, apples, bombs, and the boundary.

* ```keyboard(int key, int, int):``` </br>
Handles special key input, such as arrow keys, to control the snake's movement.

* ```checkCollision(int x1, int y1, int size1, int x2, int y2, int size2):``` </br>
Checks for collision between two objects given their coordinates and sizes.

* ```checkBombCollision():``` </br>
Checks for collision between the snake's head and a bomb, considering the bomb's tick limit.

* ```resetGame():``` </br>
Resets the game state, including the snake's length, apple positions, and other variables, preparing for a new game.

* ```update(int):``` </br>
Updates the game state, including snake movement, collision checks, and NPC updates. It also handles the bomb's ticking mechanism.

* ```keyboardRegular(unsigned char key, int x, int y):``` </br>
Handles regular key input, such as 'R' for restarting the game or ESC for exiting.

## place.cpp ##

* ```placeApple():``` </br>
- Places a regular apple randomly within game boundaries.
- Ensures no overlap with the snake's body or the bomb.
- Uses a loop for random coordinate generation until a suitable position is found.

* ```placeGoldenApple():``` </br>
- Places a golden apple with specific criteria for positioning.
- Avoids overlap with the snake, normal apples, or the bomb.
- Uses a loop to find a suitable location.

* ```placeBomb():``` </br>
- Places a bomb randomly within game boundaries.
- Ensures no immediate collision with the snake or existing apples.
- Resets the bomb's tick count and tick timer for the next round.

## main.cpp ##

* ```main(int argc, char** argv): ``` </br>
  - The main entry point of the program. Initializes GLUT, sets up the display, keyboard input, and timer for game updates.
  - It then enters the main GLUT event loop.

## Support and Feedback ##

For any issues or questions regarding the game, please feel free to open an issue in this repository. Our team will promptly address your concerns and provide assistance as needed. We appreciate your feedback and are committed to ensuring you have an enjoyable gaming experience.

Thank you for playing BoaBomb!

## Team & Work ## 

**Member Names:**
1. Ivan
2. Jenil
3. Justin
4. Sanil

### _Enjoy playing BoaBomb!_ ###

