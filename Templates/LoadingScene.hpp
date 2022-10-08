//
//  LoadingScene.hpp
//  Flappy Bird
//
//  Created by Kyle Hurd on 11/20/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//
//  Description
//
//  Within the namespace LoadingScene is one function load() that handles
//  the loading screen.
//
//  The loading screen contains a title, subtitle, and sprite of the Flappy Bird.
//  The objects are centered on the x-axis of the screen and are offsetted by the y-axis,
//  creating the loading screen image. Upon the user inputting a SPACE, the load() function
//  will return to the calling function which will be performed in main() located in the
//  main.cpp file.
//

#ifndef LoadingScene_hpp
#define LoadingScene_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Classes
#include "Classes/Bird.hpp"
#include "Classes/Pipes.hpp"
#include "Classes/helperFunctions.hpp"

#include <fstream>
#include <iostream>

namespace LoadingScene {

void load(sf::RenderWindow &);

}
#endif /* LoadingScene_hpp */
