//
//  Bird.hpp
//  SFMLProject
//
//  Created by Kyle Hurd on 11/15/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//
//  Description
//
//  Within the namespace Bird is a class BirdSprite. This class contains
//  sounds for the object and any functionality that may be needed for the
//  game to run (ex. jumping and falling)
//

#ifndef Bird_hpp
#define Bird_hpp

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "helperFunctions.hpp"

namespace Bird {

    class BirdSprite {
    private:
        const sf::Vector2i  gravity;
        sf::Vector2i        velocity; // (x,y)
        sf::Sprite          object;
        const sf::Vector2f  position;
        sf::SoundBuffer     bufferFlap;
        sf::SoundBuffer     bufferStrike;
        sf::Sound           flap;
        sf::Sound           strike;
        
    public:
        // Constructor
        BirdSprite(const sf::Texture &, int=0, int=0);
        
        // Destructor
        ~BirdSprite();
        
        // Functions
        void jump();
        void fall();
        void move(const sf::Vector2f &);
        void centerOrigin();
        void setPosition(const sf::Vector2f &);
        void setScale(float);

        sf::Vector2f getPosition();
        sf::Vector2f getTopPosition();
        sf::Vector2f getRightPosition();
        sf::Vector2f getSizeofBird();
        
        sf::Sprite getSprite();
    };
}

#endif /* Bird_hpp */
