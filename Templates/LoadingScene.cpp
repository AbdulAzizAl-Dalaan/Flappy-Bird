//
//  LoadingScene.cpp
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

#include "LoadingScene.hpp"

namespace LoadingScene {

void load(sf::RenderWindow &window) {
    print("Entered MenuScene.");
    
    const int x = 0, y = 0;
    
    // Modifying Background
    sf::Texture BackgroundTexture;
    if (!BackgroundTexture.loadFromFile("Resources/Sprites/PixeledMenuWSU1.jpg")) {
        print("Could not load PixeledMenuWSU1.jpg from file");
    }
    sf::Sprite Background(BackgroundTexture);
    Background.setScale(1.03, 1.04);
    Background.setPosition(-4, 0);
    
    // Modifying Bird Texture
    sf::Texture Birdtexture;
    if (!Birdtexture.loadFromFile("Resources/Sprites/FlappyBird.png")) {
        print("Could not load FlappyBird.png");
    }
    
    Bird::BirdSprite bird(Birdtexture, x, y);
    sf::Vector2f temp(WIDTH / 2, HEIGHT / 2 - 75);
    bird.centerOrigin();
    bird.setPosition(temp);
    
    sf::Text title;
    sf::Text subTitle;
    sf::Text userInput;
    sf::FloatRect textRect;
    sf::Font font;

    if (!font.loadFromFile("Resources/Fonts/sansation.ttf")) {
        print("Could not load sansation.ttf");
    }
    
    // Modifying the Main Title
    title.setFont(font);
    title.setString("THE FLAPPIEST BIRD");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Yellow);
    title.setOrigin(title.getLocalBounds().left + title.getLocalBounds().width / 2.0f,
                    title.getLocalBounds().top + title.getLocalBounds().height / 2.0f);
    title.setPosition((int)WIDTH / 2, (int)HEIGHT / 2);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(8);
    
    // Modifying the Sub Title
    subTitle.setFont(font);
    subTitle.setString("Press ENTER to continue...");
    subTitle.setCharacterSize(25);
    subTitle.setFillColor(sf::Color::Yellow);
    subTitle.setOrigin(subTitle.getLocalBounds().left + subTitle.getLocalBounds().width / 2,
                       subTitle.getLocalBounds().top + subTitle.getLocalBounds().height / 2);
    subTitle.setPosition((int)WIDTH / 2, (int)HEIGHT / 2 + 50);
    subTitle.setOutlineColor(sf::Color::Black);
    subTitle.setOutlineThickness(8);
    
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
                    if (event.key.code == sf::Keyboard::Enter) {
                        print("Enter key pressed.");
                        currentState = MENU;
                        return;
                    }
                    break;
                case sf::Event::KeyReleased:
                    break;
                default:
                    break;
            }
        }
        window.clear(sf::Color::Black);
        window.draw(Background);
        window.draw(title);
        window.draw(subTitle);
        window.draw(userInput);
        window.draw(bird.getSprite());
        window.display();
    }
}

}
