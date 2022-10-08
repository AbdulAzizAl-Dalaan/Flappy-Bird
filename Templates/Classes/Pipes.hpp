//
//  Pipes.hpp
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

#ifndef Pipes_hpp
#define Pipes_hpp

#include <iostream>
#include "helperFunctions.hpp"
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Pipe {

struct Pipe {
    sf::RectangleShape top;
    sf::RectangleShape bottom;
    sf::RectangleShape hole;
};

class PipesSprite {
private:
    const int numPipes;
    const int width;
    const int sizeofHole;
    Pipe PipeList[2];
    
    const sf::Vector2f velocity;
    const sf::Vector2f holeSize;
    
    sf::Texture texture;
    
public:
    // Constructor
    PipesSprite(int,int);
    void initPipes();
    
    // Destructor
    ~PipesSprite();
    
    // Functions
    void updatePipes();
    void randPipe(int i);
    void stopPipes();
    sf::Vector2f getHolePosition(int i);
    // getSize();

    // Getters
    sf::RectangleShape getTop(int i);
    sf::RectangleShape getHole(int i);
    sf::RectangleShape getBottom(int i);

    sf::Vector2f getPosition(int i);
    sf::Vector2f getHoleSize();

    int getNumPipes();
};
}

#endif /* Pipes_hpp */
