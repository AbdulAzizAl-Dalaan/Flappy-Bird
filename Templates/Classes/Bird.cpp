//
//  Bird.cpp
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

#include "Bird.hpp"

namespace Bird {

    /* *
     *  Created by:  Kyle Hurd
     *  Modified:    11/28/2020
     *  Description: Initializer for BirdSprite class. Parameters are the
     *               objects texture and the initial position of object,
     *               which have default values of x = y = 0. Object has its
     *               own gravity and velocity. Gravity is constant and velocity
     *               has a constant upward force for the jump. Also loads in
     *               a sound for the bird's flap and collision.
     */
    BirdSprite::BirdSprite(const sf::Texture &pTexture, int x, int y) :
        object(pTexture), position(x, y),
            gravity(0, 1), velocity(0, -15) {
                object.setPosition(position.x, position.y);
                currentState = LOSE;
                object.setScale(0.30, 0.30);
                if (!bufferFlap.loadFromFile("Resources/Sounds/BirdFlap.wav")) {
                    print("Could not open BirdFlap.wav");
                }
                flap.setBuffer(bufferFlap);
                if (!bufferStrike.loadFromFile("Resources/Sounds/BirdStrike.wav")) {
                    print("Could not open BirdStrike.wav");
                }
                strike.setBuffer(bufferStrike);
            }

    BirdSprite::~BirdSprite() {}

    /* *
     *  Created by:  Kyle Hurd
     *  Modified:    11/28/2020
     *  Description: Reinitializes the velocity back to its original
     *               value and moves object at that velocity. Also
     *               calls for the flapping sound effect to play.
     *               This function is state dependent. The currentState
     *               is a global function located in the helperFunctions file.
     *
     *               It is important to note that this function will update
     *               the state from LOSE to RUN automatically. There is no
     *               need to update the state when starting the game.
     */
    void BirdSprite::jump() {
        // Resetting Velocity
        switch (currentState) {
            case LOSE:
                currentState = RUN;
            case RUN:
                velocity.y = -18;
                object.move(velocity.x, velocity.y);
                flap.play();
                break;
            default: // Bug, state should only be LOSE or RUN when jump() is called.
                print("BirdSprite::jump() default case was called.\n"
                      "jump() must only be called when in the LOSE or RUN state.");
                break;
        }
    }

    /* *
     *  Created by:  Kyle Hurd
     *  Modified:    11/28/2020
     *  Description: As long as the bird object is above the maximum height limit,
     *               fall() will increase the objects velocity by adding the gravity
     *               constant to it. This is found in the first 'if' statement. The
     *               proceeding else-if detects if the bird struck the ground (the
     *               maximum HEIGHT limit).
     *
     *               For any external detections, like a collision
     *               with a pipe, fall() will check if the bird was relocated to its origin
     *               and if another function updated the state to LOSE and prevent the velocity
     *               from being altered.
     */
    void BirdSprite::fall() {
        
        if ((object.getPosition().y < -100) && currentState == RUN) {
            object.setPosition(position.x, position.y);
            strike.play();
            currentState = LOSE;
            print("The bird flew too high.\nGoodbye sweet bird.");
        }
        else if ((object.getPosition().y < HEIGHT) && currentState == RUN) {
            velocity.y += gravity.y;
            object.move(velocity.x, velocity.y);
        }
        else if ((object.getPosition().y >= HEIGHT) && currentState == RUN) {
            object.setPosition(position.x, position.y);
            strike.play();
            currentState = LOSE;
            print("Player hit the ground\nPlayer lost.");
        }
        else if ((currentState == LOSE) && !(object.getPosition() == position)) {
            object.setPosition(position.x, position.y);
            strike.play();
            print("Player hit pipe\nPlayer lost.");
        }
    }
    
    /* *
     *  Created by:  Kyle Hurd
     *  Modified:    11/28/2020
     *  Description: Changes the birds origin from the top left corner to the
     *               very center of the object.
     */
    void BirdSprite::centerOrigin() {
        object.setOrigin(object.getLocalBounds().left +
                                   object.getLocalBounds().width / 2,
                                   object.getLocalBounds().top +
                                   object.getLocalBounds().height / 2);
    }

    // **Getters and Setters** //
    /* *
    *  Created by:  Kyle Hurd
    *  Modified:    11/28/2020
    *  Description: A setter for a private member of the Sprite() class created
    *               by SFML.
    */
    void BirdSprite::move(const sf::Vector2f &v) {
        object.move(v);
    }

    // **Getters and Setters** //
    /* *
     *  Created by:  Kyle Hurd
     *  Modified:    11/28/2020
     *  Description: Sets a new scale for the object (the bird). Note that this function
     *               is scaling the current size of the object, not the original size.
     */
    void BirdSprite::setScale(float s) {
        object.scale(s, s);
    }
    
    /* *
     *  Created by:  Kyle Hurd
     *  Modified:    11/28/2020
     *  Description: Sets the position based on the origin of the object. There is only one
     *               function for this and no variants, so you must pass in a sf::Vector2f type.
     */
    void BirdSprite::setPosition(const sf::Vector2f &position) {
        object.setPosition(position);
    }

    /* *
     *  Created by:  Kyle Hurd
     *  Modified:    11/28/2020
     *  Description: Returns the top position of the object. This a global bounds and not
     *               a local, so it is the top position in relation to the window, not itself.
     */
    sf::Vector2f BirdSprite::getTopPosition() {
        sf::Vector2f temp(object.getPosition().x, object.getGlobalBounds().top);
        return temp;
    }

    /* *
     *  Created by:  Kyle Hurd
     *  Modifed:     11/28/2020
     *  Description: Returns the right position of the object. This a global bounds and not
     *               a local, so it is the right position in relation to the window, not itself.
     */
    sf::Vector2f BirdSprite::getRightPosition() {
        float x = object.getPosition().x - object.getGlobalBounds().left;
        x = object.getPosition().x + x;
        sf::Vector2f temp(x, object.getPosition().y);
        return temp;
    }

    /* *
     *  Created by:  Kyle Hurd
     *  Modified:    11/28/2020
     *  Description: Returns the dimensions of the object. This function is a local bounds,
     *               meaning it returns the width (x position) and height (y position) in
     *               relation to itself.
     */
    sf::Vector2f BirdSprite::getSizeofBird() {
        sf::Vector2f temp(object.getLocalBounds().width, object.getLocalBounds().height);
        return temp;
    }

    /* *
     *  Created by:  Kyle Hurd
     *  Modified:    11/28/2020
     *  Description: Returns the current position of the object.
     */
    sf::Vector2f BirdSprite::getPosition() {
        return object.getPosition();
    }

    /* *
     *  Created by:  Kyle Hurd
     *  Modified:    11/28/2020
     *  Description: Returns the object sprite (the bird).
     */
    sf::Sprite BirdSprite::getSprite() {
        return object;
    }
}
