//
//  GameScene.cpp
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

#include "GameScene.hpp"

namespace GameScene {

void game(sf::RenderWindow &window) {
    
    print("Entering GameScene.");
    currentState = LOSE;
    bool flag = false;
    const int x = 50, y = 200;
    
    sf::Texture Birdtexture;
    sf::Texture BackgroundTexture;
    
    sf::SoundBuffer buffer;
    sf::Sound point;
    buffer.loadFromFile("Resources/Sounds/Point.wav");
    point.setBuffer(buffer);
    
    int BGx = 0, BGy = 0;
    if (!BackgroundTexture.loadFromFile("Resources/Sprites/WSUpixeledbackground.jpg")) {
        print("Could not load WSUpixeledbackground.jpg");
    }
    sf::Sprite Background;
    Background.setTexture(BackgroundTexture);
    Background.setPosition(BGx, BGy);
    
    if (!Birdtexture.loadFromFile("Resources/Sprites/FlappyBird.png")) {
        print("Could not load FlappyBird.png");
    }
    Bird::BirdSprite bird(Birdtexture, x, y);
    bird.centerOrigin();

    Pipe::PipesSprite PipesObj(150,350); // HardCoded, change later?
    
    // Modifying Score
    sf::Font font;
    if (!font.loadFromFile("Resources/Fonts/sansation.ttf")) {
        print("Could not open sansation.ttf");
    }
    sf::Text points;
    points.setFont(font);
    points.setCharacterSize(40);
    points.setString(numToString(playerStats.currentScore));
    points.setPosition(WIDTH - 100, 25);
    points.setOutlineColor(sf::Color::Black);
    points.setOutlineThickness(8);
    
    // Modifying Instructions
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setCharacterSize(25);
    instructions.setString("Press 'SPACE' to begin...\n"
                           "Press 'M' to return to menu...");
    instructions.setPosition(50, 40);
    instructions.setFillColor(sf::Color::Yellow);
    instructions.setOutlineColor(sf::Color::Black);
    instructions.setOutlineThickness(8);
    
    // Modifying Window
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                        print("Window is closed.");
                    }
                    if (event.key.code == sf::Keyboard::Space) {
                        bird.jump();
                        currentState = RUN;
                        print("Space bar pressed.");
                    }
                    if (event.key.code == sf::Keyboard::M && currentState == LOSE) {
                        currentState = MENU;
                        return; // return to main()
                    }
                    break;
                case sf::Event::KeyReleased:
                    break;
                default:
                    break;
            }
        }
        bird.fall();
        if (currentState == LOSE && flag == false) {
            PipesObj.initPipes();
            flag = true;
        }
        else if (currentState == RUN && flag == true) {
            playerStats.currentScore = 0;
            flag = false;
        }


        for (int i = 0; i < PipesObj.getNumPipes(); i++) {

            /* THIS SWITCH CASE ONLY WORKS IF THE VELOCITY.X is -2.0, and BOTH PIPE-X-SIZE AND PIPE DISTANCE ARE EVEN NUMBERS */
    
            if (!checkCollision(bird.getTopPosition(), bird.getRightPosition(),PipesObj.getHolePosition(i), 
                PipesObj.getHoleSize())) 
            {
                switch ((int)PipesObj.getPosition(i).x) {
                case -150:
                    Background.setPosition(BGx -= 5, BGy);
                    PipesObj.randPipe(i);
                    break;
                case 50:
                    playerStats.currentScore++;
                    point.play();
                    break;
                default:
                    break;
                }
            }
            else {
                currentState = LOSE;
                std::fstream outfile;
                openOutFile(outfile, "Resources/FlappyBirdData.csv");
                updateHighScoreData(outfile);
                outfile.close();
            }
        }
        points.setString(numToString(playerStats.currentScore));
        PipesObj.updatePipes();
        window.clear(sf::Color::Black);
        window.draw(Background);
        if (currentState == LOSE) window.draw(instructions);
        for (int i = 0; i < PipesObj.getNumPipes(); i++) {
            window.draw(PipesObj.getTop(i));
            window.draw(PipesObj.getBottom(i));
            window.draw(PipesObj.getHole(i));
        }
        window.draw(points);
        window.draw(bird.getSprite());
        window.display();
    }

}
}
