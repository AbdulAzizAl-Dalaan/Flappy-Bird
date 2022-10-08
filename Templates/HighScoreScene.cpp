//
//  HighScoreScene.cpp
//  FlappyBird
//
//  Created by Kyle Hurd on 11/25/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//
//  Description
//
//  HighScoreScene is a subset of MenuScene. The scene is very simple
//  and only displays the top 10 scores from the game. These high scores
//  are saved within the FlappyBirdData.csv file located in ./Resources.
//  The user can go back to the MenuScene by pressing 'M'.
//

#include "HighScoreScene.hpp"

namespace HighScoreScene {

void highscore(sf::RenderWindow &window) {
    print("Entering HighScoreScene");
    
    // Loading in Font
    sf::Font font;
    if (!font.loadFromFile("Resources/Fonts/sansation.ttf")) {
        print("Could not load sansation.ttf");
    }
    
    // Modifying Background
    sf::Texture BackgroundTexture;
    if (!BackgroundTexture.loadFromFile("Resources/Sprites/PixeledMenuWSU1.jpg")) {
        print("Could not load PixeledMenuWSU1.jpg from file");
    }
    sf::Sprite Background(BackgroundTexture);
    Background.setScale(1.03, 1.04);
    Background.setPosition(-4, 0);
    
    // Modifying Main Title
    sf::Text mainTitle;
    mainTitle.setFont(font);
    mainTitle.setString("HIGH SCORES");
    mainTitle.setStyle(sf::Text::Underlined);
    mainTitle.setCharacterSize(50);
    mainTitle.setFillColor(sf::Color::Yellow);
    mainTitle.setOrigin(mainTitle.getLocalBounds().left + mainTitle.getLocalBounds().width / 2.0f,
                         mainTitle.getLocalBounds().top + mainTitle.getLocalBounds().height / 2.0f);
    mainTitle.setPosition((int) WIDTH / 2, (int) 50);
    mainTitle.setOutlineColor(sf::Color::Black);
    mainTitle.setOutlineThickness(8);
    
    // Modifying Instruction Text
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Press 'M' to return to Main Menu");
    instructions.setCharacterSize(25);
    instructions.setFillColor(sf::Color::Yellow);
    instructions.setPosition(25, HEIGHT - 50);
    instructions.setOutlineColor(sf::Color::Black);
    instructions.setOutlineThickness(8);
    
    // Modifying Scores
    sf::Text scores[10];
    int offset = 0;
    for (int i = 0; i < 10; i++) {
        scores[i].setFont(font);
        scores[i].setString(highScores[i].username + "    " + numToString(highScores[i].currentScore));
        scores[i].setCharacterSize(30);
        scores[i].setFillColor(sf::Color::Yellow);
        scores[i].setOrigin(scores[i].getLocalBounds().left + scores[i].getLocalBounds().width / 2.0f,
                            scores[i].getLocalBounds().top + scores[i].getLocalBounds().height / 2.0f);
        scores[i].setPosition(WIDTH / 2, 150 + offset);
        scores[i].setOutlineColor(sf::Color::Black);
        scores[i].setOutlineThickness(8);
        offset += 75;
    }
    
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
                    if (event.key.code == sf::Keyboard::M) {
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
        
        window.clear();
        window.draw(Background);
        window.draw(mainTitle);
        for (int i = 0; i < 10; i++) {
            window.draw(scores[i]);
        }
        window.draw(instructions);
        window.display();
    }
}

}
