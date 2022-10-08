//
//  InvadersScene.hpp
//  FlappyBird
//
//  Created by Kyle Hurd on 12/4/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//
//  Description
//
//  InvadersScene is the second version of the Flappy Bird
//  game that mimics the functionality of Space Invaders.
//  In this version, enemy birds fly at you, if you are struck by
//  the enemy birds, you lose.
//

#ifndef InvadersScene_hpp
#define InvadersScene_hpp

// SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Classes
#include "Classes/Bird.hpp"
#include "Classes/helperFunctions.hpp"
#include "Classes/Laser.hpp"
#include "Classes/Enemy.hpp"

// Other
#include <iostream>
#include <sstream>
#include <cstring>

namespace InvadersScene {

void game(sf::RenderWindow &);

}

#endif /* InvadersScene_hpp */
