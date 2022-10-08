//
//  Laser.hpp
//  SFMLProject
//
//  Created by Justin Pilgrim on 11/19/20.
//  Copyright © 2020 Justin Pilgrim. All rights reserved.
//
//  Description
//
//  Laser.cpp is the class functions for the Laser class which
//  is used for the Flappy Invaders game mode of the Flappy Bird program.
//

#ifndef Laser_hpp
#define Laser_hpp

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Classes
#include "Bird.hpp"

// Other
#include <iostream>

namespace LaserSprite {

class Laser {
private:
    bool             fired[5]; // In play
    sf::Vector2i     velocity[5];
    sf::Sprite       object[5];
    sf::Sound        laserSound;
    sf::SoundBuffer  buffer;
    
public:
    // Constructor/Destructor
    Laser(const sf::Texture &);
    ~Laser();
    
    // Laser Object functions
    void shoot(Bird::BirdSprite &, int);
    void moveLaser(int);
    
    // Getters
    sf::Sprite getSprite(int);
    int getPositionX(int);
    int getPositionY(int);
};

}

#endif /* Laser.hpp */
