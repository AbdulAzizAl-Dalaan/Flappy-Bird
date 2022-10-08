//
//  helperFunctions.hpp
//  Flappy Bird
//
//  Created by Kyle Hurd and Abdul Aziz Al-Dalaan on 11/15/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//
//  Description
//
//  This .hpp and .cpp files are designed to provide any additional
//  functions needed to implement the game.
//
//  The extern int is declared here to create a global variable for all the
//  classes and Scenes to view to check the current state of the game. Depending
//  on the state, the classes will compare their state with the global state
//  to ensure the functionality is acting as it should. More information of the
//  other functions is written in the function definition.
//

#ifndef helperFunctions_hpp
#define helperFunctions_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

#define WIDTH   800
#define HEIGHT  1000

enum State { RUN, LOSE, LOAD, MENU, NORMAL, INVADERS, HIGHSCORE, UPDATENAME, CREDITS };

struct GameData {
    std::string     username;
    int             currentScore;
};

// Global Declarations
extern GameData playerStats;
extern GameData highScores[10];
extern int currentState;
extern const int laserSpeed;

// Displaying Data
void print(std::string n = "", std::ostream & = std::cout);
void openInFile(std::fstream &, std::string);
void openOutFile(std::fstream &, std::string);

// Collision Detectors
bool checkCollision(sf::Vector2f, sf::Vector2f,
                        sf::Vector2f, sf::Vector2f);
bool checkCollision(sf::Vector2f, sf::Vector2f, sf::Vector2f);

// Convert Num to a String
std::string numToString(int);

// Modifying Game Data
void bubbleSortGameData();
void getHighScoreData(std::fstream &);
void updateHighScoreData(std::fstream &);

// Operator Overloading for Vectors
bool operator== (const sf::Vector2f &, const sf::Vector2f &);

#endif /* helperFunctions_hpp */
