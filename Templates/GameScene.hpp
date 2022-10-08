//
//  GameScene.hpp
//  Flappy Bird
//
//  Created by Kyle Hurd and Abdul Aziz Al-Dalaan on 11/21/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//
//  Description
//
//  Within the namespace GameScene there is one function to run the
//  active section of the game.
//
//  The GameScene contains a Bird object and Pipes object. The bird will
//  fly within the bounds of the window and avoid the pipes moving towards it.
//  Within the helperFunctions file, an error detection function was created
//  to determine whether the two objects have come in contact with one another.
//  If this function detects a collision, the GameScene will then change the global
//  variable of the state to the LOSE condition.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Classes
#include "Classes/Bird.hpp"
#include "Classes/Pipes.hpp"
#include "Classes/helperFunctions.hpp"

#include <fstream>
#include <iostream>

namespace GameScene {

void game(sf::RenderWindow &);

}

#endif /* GameScene_hpp */
