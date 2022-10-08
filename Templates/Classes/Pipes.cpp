//
//  Pipes.cpp
//  Flappy Bird
//
//  Created by Abdul Aziz Al-Dalaan and Kyle Hurd on 11/16/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//
//  Description
//
//  Within the Pipe namespace there is a struct defenition and class declaration.
//
//  The Pipe struct contains three RectangleShape objects representing the top,
//  bottom, and space between the two pipes. The 'hole' is desgined to be the
//  safe zone for the bird. If the perimeter of the bird exceeds this safe zone
//  then the player loses the game.
//

#include "Pipes.hpp"

namespace Pipe {

/* *
 *  Created by:  Kyle Hurd and Abdul Aziz Al-Dalaan
 *  Modified:    11/28/2020
 *  Description: Initializer for the class. Sets private variables
 *               for velocity, numPipes, width, and sizeofHole.
 *               After these intializations, it calls a function
 *               initPipes() to create the rest of the objects.
 */
PipesSprite::PipesSprite(int w, int s) :
    velocity(-2.0 , 0), numPipes(2),
        width(w), sizeofHole(s), holeSize(w, s) { 
    initPipes();
}

PipesSprite::~PipesSprite() {}

/* *
 *  Created by:  Kyle Hurd and Abdul Aziz Al-Dalaan
 *  Modified:    11/28/2020
 *  Description: Randomizes the location of the hole for each
 *               pipe and places them on the window starting
 *               from the middle to an offset of 600 pixels apart
 *               for each pipe. A texture is also added to the top
 *               and bottom pipe. 'hole' is transparent.
 */
void PipesSprite::initPipes() {
    // Initial Offset for pipe
    int offset = (int) WIDTH / 2;
    
    for (int i = 0; i < numPipes; i++) {
        
        // Temp Vector to Modify Vector Components for Each Pipe
        sf::Vector2f temp(width, sizeofHole);
        
        // Setting the Size
        PipeList[i].hole.setSize(temp);
        temp.y = rand() % 451 + 100;
        PipeList[i].top.setSize(temp);
        temp.y = HEIGHT - PipeList[i].top.getSize().y - PipeList[i].hole.getSize().y;
        PipeList[i].bottom.setSize(temp);

        // Setting the Position
        temp.x = offset;
        temp.y = 0;
        PipeList[i].top.setPosition(temp);
        temp.y = PipeList[i].top.getSize().y;
        PipeList[i].hole.setPosition(temp);
        temp.y = HEIGHT - PipeList[i].bottom.getSize().y;
        PipeList[i].bottom.setPosition(temp);

        /* Setting pipe colors (could later include a texture) */
        texture.loadFromFile("Resources/Sprites/Pipes.png");
        PipeList[i].hole.setFillColor(sf::Color::Transparent);
        PipeList[i].top.setTexture(&texture);
        PipeList[i].bottom.setTexture(&texture);

        offset += 600; // increments for the distance of the next pipe
    }
}

/* *
 *  Created by:  Kyle Hurd and Abdul Aziz Al-Dalaan
 *  Modified:    11/28/2020
 *  Description: Moves each pipe in a direction specified by the
 *               velocity vector.
 */
void PipesSprite::updatePipes() {
    if (currentState == RUN) {
        for (int i = 0; i < numPipes; i++) {
            PipeList[i].top.move(velocity);
            PipeList[i].hole.move(velocity);
            PipeList[i].bottom.move(velocity);
        }
    }
}

/* *
 *  Created by:  Kyle Hurd and Abdul Aziz Al-Dalaan
 *  Modified:    11/28/2020
 *  Description: Sets each pipe movement to zero. This code is irrelevant
 *               to our project and was not used as we can simply not call
 *               the function updatePipes() and the same effect will occur.
 */
void PipesSprite::stopPipes() { // Irrelevant?
    if (currentState == LOSE) {
        for (int i = 0; i < numPipes; i++) {
            PipeList[i].top.move(0,0);
            PipeList[i].hole.move(0,0);
            PipeList[i].bottom.move(0,0);
        }
    }
}

// **GETTERS** //
sf::RectangleShape PipesSprite::getTop(int i) {
    return PipeList[i].top;
}

sf::RectangleShape PipesSprite::getHole(int i) {
    return PipeList[i].hole;
}

sf::RectangleShape PipesSprite::getBottom(int i) {
    return PipeList[i].bottom;
}

sf::Vector2f PipesSprite::getPosition(int i) {
    return PipeList[i].top.getPosition();
}

sf::Vector2f PipesSprite::getHolePosition(int i) { // pass in nearest pipe index either 0 or 1
    return PipeList[i].hole.getPosition();
}

sf::Vector2f PipesSprite::getHoleSize() {
    return holeSize;
}

int PipesSprite::getNumPipes() {
    return numPipes;
}

/* *
 *  Created by:  Kyle Hurd and Abdul Aziz Al-Dalaan
 *  Modified:    11/28/2020
 *  Description: Changes the location of the hole between the top and
 *               bottom pipe. After updating the location of the hole,
 *               the pipe is placed in the back of the line where it will
 *               wait to move back into the window. Or not.
 */
void PipesSprite::randPipe(int i) {

    int nextXposition = 0;
    sf::Vector2f temp(width, rand() % 451 + 100);
    
    // Set Size of top and bottom pipe.
    // Hole is a constant, does not need changed
    PipeList[i].top.setSize(temp);
    temp.y = HEIGHT - sizeofHole - PipeList[i].top.getSize().y;
    PipeList[i].bottom.setSize(temp);

    // Updating the next x position
    // Grab the position of next pipe and add an offset of 3/4 the width
    // nextXposition++;
    // nextXposition = (nextXposition & 1) + 600;
    nextXposition = (i != 0) ? (PipeList[i - 1].top.getPosition().x) :
                                (PipeList[numPipes - 1].top.getPosition().x);
    
    nextXposition = nextXposition + 600;
    // Set Position of top, bottom, and hole
    temp.x = nextXposition; temp.y = 0;
    PipeList[i].top.setPosition(temp);
    temp.y = PipeList[i].top.getSize().y;
    PipeList[i].hole.setPosition(temp);
    temp.y = HEIGHT - PipeList[i].bottom.getSize().y;
    PipeList[i].bottom.setPosition(temp);
}
}
