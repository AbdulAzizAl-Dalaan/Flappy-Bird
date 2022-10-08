//
//  MenuScene.cpp
//  FlappyBird
//
//  Created by Kyle Hurd on 11/25/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//
//  Description
//
//  In the menu scene, the user playing the game has the ability to use
//  the arrow keys and ENTER button to select an item from the menu options
//  list. When one of the menu items is selected (such as high scores, change
//  name, normal mode, etc.) the menu scene detects which item the user wants
//  to go to and updates the currentState, a global variable declared in the
//  helperFunctions file. Upon updating the state, the scene returns to main()
//  [or the function call] without performing any more actions.
//

#ifndef MenuScene_hpp
#define MenuScene_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Classes
#include "Classes/Bird.hpp"
#include "Classes/Pipes.hpp"
#include "Classes/helperFunctions.hpp"

#include <fstream>
#include <iostream>

namespace MenuScene {

void menu(sf::RenderWindow &);

}
#endif /* MenuScene_hpp */
