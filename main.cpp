
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Classes
#include "Templates/Classes/Bird.hpp"
#include "Templates/Classes/Pipes.hpp"

// Scenes
#include "Templates/LoadingScene.hpp"
#include "Templates/GameScene.hpp"
#include "Templates/MenuScene.hpp"
#include "Templates/HighScoreScene.hpp"
#include "Templates/ChangeNameScene.hpp"
#include "Templates/CreditScene.hpp"
#include "Templates/InvadersScene.hpp"

// Other
#include "Templates/Classes/helperFunctions.hpp"
#include <fstream>
#include <iostream>
#include <random>

int main() {
    
    // Initializing Globals
    playerStats.username     = "";
    playerStats.currentScore = 0;
    currentState = LOAD;
    
    // Creating Window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "FLAPPY BIRD WSU EDITION TEST");
    window.setFramerateLimit(75);
    window.setKeyRepeatEnabled(false);
    
    // Randomize
    srand((unsigned int)time(NULL));
    
    // Loading Info from File to Program
    std::fstream infile;
    openInFile(infile, "Resources/FlappyBirdData.csv");
    getHighScoreData(infile);
    infile.close();
    
    // State Machine
    while (window.isOpen()) {
        switch (currentState) {
            case LOAD:
                LoadingScene::load(window);
                break;
            case NORMAL:
                GameScene::game(window);
                break;
            case MENU:
                MenuScene::menu(window);
                break;
            case HIGHSCORE:
                HighScoreScene::highscore(window);
                break;
            case UPDATENAME:
                ChangeNameScene::changeName(window);
                break;
            case INVADERS:
                InvadersScene::game(window);
                break;
            case CREDITS:
                CreditScene::credits(window);
                break;
            default:
                print("Error in game. No viable state found\nLeaving game.");
                return EXIT_FAILURE;
                break;
        }
    }
    
    return EXIT_SUCCESS;
}
