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

#include "MenuScene.hpp"

namespace MenuScene {

void menu(sf::RenderWindow &window) {
    print("Entering MenuScene");
    
    const int x = 0, y = 0;
    sf::Texture Birdtexture;
    
    sf::Texture BackgroundTexture;
    if (!BackgroundTexture.loadFromFile("Resources/Sprites/PixeledMenuWSU1.jpg")) {
        print("Could not load PixeledMenuWSU1.jpg from file");
    }
    sf::Sprite Background(BackgroundTexture);
    Background.setScale(1.03, 1.04);
    Background.setPosition(-4, 0);
    
    if (!Birdtexture.loadFromFile("Resources/Sprites/FlappyBird.png")) {
        print("Could not load FlappyBird.png");
    }
    
    sf::Vector2f birdHSPos(50, 260);
    sf::Vector2f birdCNPos(50, 360);
    sf::Vector2f birdNMPos(50, 460);
    sf::Vector2f birdFIPos(50, 560);
    sf::Vector2f birdCSPos(50, 660);
    sf::Vector2f birdEXPos(50, 760);
    
    Bird::BirdSprite bird(Birdtexture, x, y);
    bird.setScale(0.7);
    bird.centerOrigin();
    bird.setPosition(birdHSPos);
    
    Bird::BirdSprite moveableObj(Birdtexture, x, y);
    moveableObj.centerOrigin();
    moveableObj.setPosition(sf::Vector2f(-45, HEIGHT - 75));
    
    sf::Font font;
    if (!font.loadFromFile("Resources/Fonts/sansation.ttf")) {
        print("Could not load sansation.ttf");
    }
    
    // Modifying Main Title
    sf::Text mainTitle;
    mainTitle.setFont(font);
    mainTitle.setString("THE FLAPPIEST BIRD");
    mainTitle.setStyle(sf::Text::Underlined);
    mainTitle.setCharacterSize(50);
    mainTitle.setFillColor(sf::Color::Yellow);
    mainTitle.setOrigin(mainTitle.getLocalBounds().left + mainTitle.getLocalBounds().width / 2.0f,
                         mainTitle.getLocalBounds().top + mainTitle.getLocalBounds().height / 2.0f);
    mainTitle.setPosition((int) WIDTH / 2, (int) 50);
    mainTitle.setOutlineColor(sf::Color::Black);
    mainTitle.setOutlineThickness(8);
    
    // Modifying Greet
    sf::Text greeting;
    greeting.setFont(font);
    greeting.setString("Hello, " + playerStats.username + "!");
    greeting.setCharacterSize(30);
    greeting.setFillColor(sf::Color::Yellow);
    greeting.setPosition(50, 100);
    greeting.setOutlineColor(sf::Color::Black);
    greeting.setOutlineThickness(8);
    
    // Modifying Instructions
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Use UP and DOWN arrows and ENTER to select an option...");
    instructions.setCharacterSize(25);
    instructions.setFillColor(sf::Color::Yellow);
    instructions.setPosition(30, HEIGHT - 40);
    instructions.setOutlineColor(sf::Color::Black);
    instructions.setOutlineThickness(8);
    
    // Modifying High Score
    sf::Text highScores;
    highScores.setFont(font);
    highScores.setString("High Scores");
    highScores.setCharacterSize(30);
    highScores.setFillColor(sf::Color::Yellow);
    highScores.setPosition(100, 250);
    highScores.setOutlineColor(sf::Color::Black);
    highScores.setOutlineThickness(8);
    
    // Modfying Change Name
    sf::Text changeName;
    changeName.setFont(font);
    changeName.setString("Change Name");
    changeName.setCharacterSize(30);
    changeName.setFillColor(sf::Color::Yellow);
    changeName.setPosition(100, 350);
    changeName.setOutlineColor(sf::Color::Black);
    changeName.setOutlineThickness(8);
    
    // Modifying Normal Mode
    sf::Text normalMode;
    normalMode.setFont(font);
    normalMode.setString("Normal Mode");
    normalMode.setCharacterSize(30);
    normalMode.setFillColor(sf::Color::Yellow);
    normalMode.setPosition(100, 450);
    normalMode.setOutlineColor(sf::Color::Black);
    normalMode.setOutlineThickness(8);
    
    // Modifying Flappy Invaders
    sf::Text invadersMode;
    invadersMode.setFont(font);
    invadersMode.setString("Flappy Invaders");
    invadersMode.setCharacterSize(30);
    invadersMode.setFillColor(sf::Color::Yellow);
    invadersMode.setPosition(100, 550);
    invadersMode.setOutlineColor(sf::Color::Black);
    invadersMode.setOutlineThickness(8);
    
    // Modifying Credits Title
    sf::Text credits;
    credits.setFont(font);
    credits.setString("Credits");
    credits.setCharacterSize(30);
    credits.setFillColor(sf::Color::Yellow);
    credits.setPosition(100, 650);
    credits.setOutlineColor(sf::Color::Black);
    credits.setOutlineThickness(8);
    
    // Modifying Exit Title
    sf::Text exit;
    exit.setFont(font);
    exit.setString("Exit");
    exit.setCharacterSize(30);
    exit.setFillColor(sf::Color::Yellow);
    exit.setPosition(100, 750);
    exit.setOutlineColor(sf::Color::Black);
    exit.setOutlineThickness(8);
    
    // Setting Sound
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Resources/Sounds/Click.wav")) {
        print("Unable to load Click.wav");
    }
    sf::Sound click;
    click.setBuffer(buffer);
    
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
                    /* *
                     *  Updates the state dependent on the location
                     *  of the bird. The switch case in main() will
                     *  then call the scene tied to said state.
                     */
                    if (event.key.code == sf::Keyboard::Enter) {
                        print("Enter key pressed.");
                        if (bird.getPosition() == birdHSPos)
                            currentState = HIGHSCORE;
                        else if (bird.getPosition() == birdCNPos)
                            currentState = UPDATENAME;
                        else if (bird.getPosition() == birdNMPos)
                            currentState = NORMAL;
                        else if (bird.getPosition() == birdFIPos)
                            currentState = INVADERS;
                        else if (bird.getPosition() == birdCSPos)
                            currentState = CREDITS;
                        else if (bird.getPosition() == birdEXPos)
                            window.close();
                        return; // return to main()
                    }
                    /* *
                     *  Moves the bird obect up or down the menu
                     *  items.
                     */
                    if (event.key.code == sf::Keyboard::Up) {
                        print("Up key pressed");
                        click.play();
                        if (bird.getPosition() == birdHSPos)
                            bird.setPosition(birdEXPos);
                        else if (bird.getPosition() == birdCNPos)
                            bird.setPosition(birdHSPos);
                        else if (bird.getPosition() == birdNMPos)
                            bird.setPosition(birdCNPos);
                        else if (bird.getPosition() == birdFIPos)
                            bird.setPosition(birdNMPos);
                        else if (bird.getPosition() == birdCSPos)
                            bird.setPosition(birdFIPos);
                        else if (bird.getPosition() == birdEXPos)
                            bird.setPosition(birdCSPos);
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        print("Down key pressed");
                        click.play();
                        if (bird.getPosition() == birdHSPos)
                            bird.setPosition(birdCNPos);
                        else if (bird.getPosition() == birdCNPos)
                            bird.setPosition(birdNMPos);
                        else if (bird.getPosition() == birdNMPos)
                            bird.setPosition(birdFIPos);
                        else if (bird.getPosition() == birdFIPos)
                            bird.setPosition(birdCSPos);
                        else if (bird.getPosition() == birdCSPos)
                            bird.setPosition(birdEXPos);
                        else if (bird.getPosition() == birdEXPos)
                            bird.setPosition(birdHSPos);
                    }
                    break;
                case sf::Event::KeyReleased:
                    break;
                default:
                    break;
            }
        }
        moveableObj.move(sf::Vector2f(1,0));
        if (moveableObj.getPosition().x > WIDTH + 45)
            moveableObj.setPosition(sf::Vector2f(-45, HEIGHT - 75));
        
        // Drawing Items to Window
        window.clear(sf::Color::Black);
        window.draw(Background);
        window.draw(mainTitle);
        window.draw(instructions);
        window.draw(greeting);
        window.draw(highScores);
        window.draw(changeName);
        window.draw(normalMode);
        window.draw(invadersMode);
        window.draw(moveableObj.getSprite());
        window.draw(exit);
        window.draw(credits);
        window.draw(bird.getSprite());
        window.display();
    }
}

}
