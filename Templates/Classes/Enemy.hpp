//
//  Laser.hpp
//  SFMLProject
//
//  Created by © Justin Pilgrim on 11/23/20.
//  Copyright  2020 Justin Pilgrim. All rights reserved.
//
//  Description
//
//  Class member functions for the Enemy class for the
//  Flappy Invanders game mode of the Flappy Bird game
//

#ifndef Enemy_hpp
#define Enemy_hpp

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Classes
#include "helperFunctions.hpp"
#include "Bird.hpp"
#include "Laser.hpp"

// Other
#include <iostream>

namespace EnemySprite {

class Enemy {
private:
    sf::Vector2f             velocity;
    sf::Sprite                enemies;
    bool                          hit;
    int                     positionX; // X position
    int                     positionY; // Y position
        
public:
    Enemy(double, sf::Texture &);
    ~Enemy();
    
    void enemyDeploy();
    void enemyMove();
    sf::Sprite getSprite();
    bool enemyDestroyed(int, LaserSprite::Laser &);
    sf::Vector2f getPosition();
    void enemyReset();
};

}

#endif /* Enemy.hpp */
