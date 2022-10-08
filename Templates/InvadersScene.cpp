//
//  InvadersScene.cpp
//  Flappy Bird
//
//  Created by Justin Pilgrim
//  Copyright © 2020 Justin Pilgrim. All rights reserved.
//
//  Description
//
//  InvadersScene is the second version of the Flappy Bird
//  game that mimics the functionality of Space Invaders.
//  In this version, enemy birds fly at you, if you are struck by
//  the enemy birds, you lose.
//

#include "InvadersScene.hpp"

namespace InvadersScene {

void game(sf::RenderWindow &window) {

    const int x = 50, y = 400;
    bool check1 = false, check2 = false, check3 = false, check4 = false;

    int i = 0; // For laser

    // Modifying Font
    sf::Font Sansitation;
    if (!Sansitation.loadFromFile("Resources/Fonts/sansation.ttf")) {
        print("Could not load sansation.ttf");
    }
    
    // Modifying Score
    sf::Text score;
    score.setPosition(700, 50);
    score.setCharacterSize(55);
    score.setFillColor(sf::Color::Yellow);
    score.setFont(Sansitation);
    
    // Modifying Instructions
    sf::Text instructions;
    instructions.setFont(Sansitation);
    instructions.setCharacterSize(25);
    instructions.setString("Press 'SPACE' to begin...\n"
                           "Press 'M' to return to menu...");
    instructions.setPosition(50, 40);
    instructions.setFillColor(sf::Color::Yellow);

    // Modifying Backound Texture
    sf::Texture BackgroundTexture;
    if (!BackgroundTexture.loadFromFile("Resources/Sprites/PixeledSpace.jpg")) {
        print("Could not load PixeledSpace.jpg");
    }
    sf::Sprite Background(BackgroundTexture);
    
    // Modifying the Bird Object
    sf::Texture BirdTexture;
    if (!BirdTexture.loadFromFile("Resources/Sprites/FlappyBird.png")) {
        print("Could not load FlappyBird.png");
    }
    Bird::BirdSprite bird(BirdTexture, x, y);
    bird.centerOrigin();

    // Modifying Laser
    sf::Texture LaserTexture;
    if (!LaserTexture.loadFromFile("Resources/Sprites/Laser3.png")) {
        print("Could not load Laser1.png");
    }
    LaserSprite::Laser laser(LaserTexture);

    // Modifying the Enemy Birds
    sf::Texture EnemyTexture;
    if (!EnemyTexture.loadFromFile("Resources/Sprites/FlappyBirdEnemy.png")) {
        print("Could not load FlappyBirdEnemy.png");
    }

    EnemySprite::Enemy Enemy1(-2.0, EnemyTexture);
    EnemySprite::Enemy Enemy2(-2.0, EnemyTexture);
    EnemySprite::Enemy Enemy3(-2.0, EnemyTexture);
    EnemySprite::Enemy Enemy4(-2.0, EnemyTexture);

    // Modifying Window
    playerStats.currentScore = 0;

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
                    i %= 5; // reset laser
                    laser.shoot(bird, i++);
                    print("Space bar pressed.");
                }
                if (event.key.code == sf::Keyboard::M && currentState == LOSE) {
                    print("M key pressed.");
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

        if (currentState == RUN) {
            Enemy1.enemyDeploy(); // Deploy enemies
            Enemy2.enemyDeploy(); // Deploy enemies
            Enemy3.enemyDeploy(); // Deploy enemies
            Enemy4.enemyDeploy(); // Deploy enemies
        }
        // Check for laser collision
        for (int p = 0; p < i; p++) {
            check1 = Enemy1.enemyDestroyed(p, laser); // Enemy destroyed
            check2 = Enemy2.enemyDestroyed(p, laser); // Enemy destroyed
            check3 = Enemy3.enemyDestroyed(p, laser); // Enemy destroyed
            check4 = Enemy4.enemyDestroyed(p, laser); // Enemy destroyed
        }
        if (check1 == true) { // Update score {
            playerStats.currentScore++;
        }
        if (check2 == true) {
            playerStats.currentScore++;
        }
        if (check3 == true) {
            playerStats.currentScore++;
        }
        if (check4 == true) {
            playerStats.currentScore++;
        }
        // Update string score
        if (currentState == LOSE) { // If player loses, rest score
            playerStats.currentScore = 0;
        }
        score.setString(std::to_string(playerStats.currentScore));

        EnemySprite::Enemy enemyArray[] = {Enemy1, Enemy2, Enemy3, Enemy4};
        
        // Check enemy collisions
        for (int i = 0; i < 4; ++i) {
            if (!checkCollision(bird.getTopPosition(), bird.getRightPosition(), enemyArray[i].getPosition())) {
                currentState = LOSE;
                break;
            }
        }
        
        // Reset enemies
        Enemy1.enemyReset();
        Enemy2.enemyReset();
        Enemy3.enemyReset();
        Enemy4.enemyReset();

        // Move stuff
        if (currentState == RUN) {
            Enemy1.enemyMove(); // Move
            Enemy2.enemyMove(); // Move
            Enemy3.enemyMove(); // Move
            Enemy4.enemyMove(); // Move
        }

        for (int p = 0; p < i; p++) {
            laser.moveLaser(p);
        }

        // Draw stuff
        window.clear();
        window.draw(Background);
        window.draw(bird.getSprite());
        window.draw(score);
        for (int p = 0; p < i; p++) {
            window.draw(laser.getSprite(p));
        }
        if (currentState == RUN) {
            window.draw(Enemy1.getSprite());
            window.draw(Enemy2.getSprite());
            window.draw(Enemy3.getSprite());
            window.draw(Enemy4.getSprite());
        }
        else {
            window.draw(instructions);
        }
        window.display();
    }
    
}

}


