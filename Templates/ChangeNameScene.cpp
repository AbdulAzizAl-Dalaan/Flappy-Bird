//
//  ChangeNameScene.cpp
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

#include "ChangeNameScene.hpp"

namespace ChangeNameScene {

void changeName(sf::RenderWindow &window) {
    
    // Modifying Background
    sf::Texture BackgroundTexture;
    if (!BackgroundTexture.loadFromFile("Resources/Sprites/PixeledMenuWSU1.jpg")) {
        print("Could not load PixeledMenuWSU1.jpg from file");
    }
    sf::Sprite Background(BackgroundTexture);
    Background.setScale(1.03, 1.04);
    Background.setPosition(-4, 0);
    
    // Declaring Variables
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i = playerStats.username[0] - 65,
        j = playerStats.username[1] - 65,
        k = playerStats.username[2] - 65;
    
    // Adding a Sound
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Resources/Sounds/Click.wav")) {
        print("Unable to open Click.wav");
    }
    sf::Sound click;
    click.setBuffer(buffer);
    
    // Setting a Font
    sf::Font font;
    if (!font.loadFromFile("Resources/Fonts/sansation.ttf")) {
        print("Cannot open sansation.ttf");
    }
    
    // Modifying Main Title
    sf::Text mainTitle;
    mainTitle.setFont(font);
    mainTitle.setString("UPDATE USERNAME");
    mainTitle.setStyle(sf::Text::Underlined);
    mainTitle.setCharacterSize(50);
    mainTitle.setFillColor(sf::Color::Yellow);
    mainTitle.setOrigin(mainTitle.getLocalBounds().left + mainTitle.getLocalBounds().width / 2.0f,
                         mainTitle.getLocalBounds().top + mainTitle.getLocalBounds().height / 2.0f);
    mainTitle.setPosition((int) WIDTH / 2, (int) 50);
    mainTitle.setOutlineColor(sf::Color::Black);
    mainTitle.setOutlineThickness(8);
    
    // Modifying Instructions
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Use arrow keys to select the letters\n"
                           "Initials will automatically be saved\n"
                           "Press 'M' to return to main menu....\n");
    instructions.setCharacterSize(30);
    instructions.setFillColor(sf::Color::Yellow);
    instructions.setPosition(50, HEIGHT - 150);
    instructions.setOutlineColor(sf::Color::Black);
    instructions.setOutlineThickness(8);
    
    // Modifying userName[0]
    sf::Text userName0;
    userName0.setFont(font);
    userName0.setString((char)alphabet[i]);
    userName0.setCharacterSize(30);
    userName0.setFillColor(sf::Color::Yellow);
    userName0.setPosition((int) WIDTH / 2 - 80, 150);
    userName0.setOutlineColor(sf::Color::Black);
    userName0.setOutlineThickness(8);
    
    // Modifying userName[1]
    sf::Text userName1;
    userName1.setFont(font);
    userName1.setString((char)alphabet[j]);
    userName1.setCharacterSize(30);
    userName1.setFillColor(sf::Color::Yellow);
    userName1.setPosition((int) WIDTH / 2, 150);
    userName1.setOutlineColor(sf::Color::Black);
    userName1.setOutlineThickness(8);
    
    // Modifying userName[2]
    sf::Text userName2;
    userName2.setFont(font);
    userName2.setString((char)alphabet[k]);
    userName2.setCharacterSize(30);
    userName2.setFillColor(sf::Color::Yellow);
    userName2.setPosition((int) WIDTH / 2 + 80, 150);
    userName2.setOutlineColor(sf::Color::Black);
    userName2.setOutlineThickness(8);
    
    // Modifying Bird as Pointer
        // Locations for Bird
    sf::Vector2f birdName0PS((WIDTH / 2) - 85, 200);
    sf::Vector2f birdName1PS((WIDTH / 2)     , 200);
    sf::Vector2f birdName2PS((WIDTH / 2) + 85, 200);
    
    sf::Texture birdTexture;
    if (!birdTexture.loadFromFile("Resources/Sprites/FlappyBird.png")) {
        print("Could not load FlappyBird.png");
    }
    Bird::BirdSprite moveableObj(birdTexture, 0, 0);
    moveableObj.centerOrigin();
    moveableObj.setScale(0.6);
    moveableObj.setPosition(birdName1PS);
    
    // Modyfing the Window
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                        print("Window is closed.");
                    }
                    if (event.key.code == sf::Keyboard::M) {
                        currentState = MENU;
                        std::fstream outfile;
                        openOutFile(outfile, "Resources/FlappyBirdData.csv");
                        updateHighScoreData(outfile);
                        outfile.close();
                        return; // return to main()
                    }
                    if (event.key.code == sf::Keyboard::Up) {
                        click.play();
                        if (moveableObj.getPosition() == birdName0PS) {
                            ++i %= 26;
                            playerStats.username[0] = alphabet[i];
                        }
                        else if (moveableObj.getPosition() == birdName1PS) {
                            ++j %= 26;
                            playerStats.username[1] = alphabet[j];
                        }
                        else if (moveableObj.getPosition() == birdName2PS) {
                            ++k %= 26;
                            playerStats.username[2] = alphabet[k];
                        }
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        click.play();
                        if (moveableObj.getPosition() == birdName0PS) {
                            i = (i - 1 < 0) ? 25 : i - 1;
                            playerStats.username[0] = alphabet[i];
                        }
                        else if (moveableObj.getPosition() == birdName1PS) {
                            j = (j - 1 < 0) ? 25 : j - 1;
                            playerStats.username[1] = alphabet[j];
                        }
                        else if (moveableObj.getPosition() == birdName2PS) {
                            k = (k - 1 < 0) ? 25 : k - 1;
                            playerStats.username[2] = alphabet[k];
                        }
                    }
                    if (event.key.code == sf::Keyboard::Left) {
                        click.play();
                        if (moveableObj.getPosition() == birdName0PS)
                            moveableObj.setPosition(birdName2PS);
                        else if (moveableObj.getPosition() == birdName1PS)
                            moveableObj.setPosition(birdName0PS);
                        else if (moveableObj.getPosition() == birdName2PS)
                            moveableObj.setPosition(birdName1PS);
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                        click.play();
                        if (moveableObj.getPosition() == birdName2PS)
                            moveableObj.setPosition(birdName0PS);
                        else if (moveableObj.getPosition() == birdName1PS)
                            moveableObj.setPosition(birdName2PS);
                        else if (moveableObj.getPosition() == birdName0PS)
                            moveableObj.setPosition(birdName1PS);
                    }
                    
                case sf::Event::KeyReleased:
                    break;
                default:
                    break;
                        
            }
        }
        userName0.setString((char)alphabet[i]);
        userName1.setString((char)alphabet[j]);
        userName2.setString((char)alphabet[k]);
        
        window.clear();
        window.draw(Background);
        window.draw(mainTitle);
        window.draw(instructions);
        window.draw(userName0);
        window.draw(userName1);
        window.draw(userName2);
        window.draw(moveableObj.getSprite());
        window.display();
    }
    
    
}

}
