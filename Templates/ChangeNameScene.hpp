//
//  ChangeNameScene.hpp
//  FlappyBird
//
//  Created by Kyle Hurd on 11/27/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//
//  Description
//
//  ChangeNameScene is a subset accessed from the Menu Scene.
//  When in this scene, the user can update their username.
//  This is done via an 'arcade style' approach in which the user
//  has a three character length name that can be altered using
//  the arrow keys. We update their name via an alphabet string
//  in which the location specifiers (i,j,k) hold the current
//  character that will become their new name when exiting the
//  ChangeNameScene.
//

#ifndef ChangeNameScene_hpp
#define ChangeNameScene_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Classes
#include "Classes/Bird.hpp"
#include "Classes/Pipes.hpp"

// Other
#include "Classes/helperFunctions.hpp"
#include <fstream>
#include <iostream>

namespace ChangeNameScene {

void changeName(sf::RenderWindow &);

}

#endif /* ChangeNameScene_hpp */
