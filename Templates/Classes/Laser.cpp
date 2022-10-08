//
//  Laser.cpp
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

#include "Laser.hpp"

namespace LaserSprite {

    /* *
     *  Created by:  Justin Pilgrim and Kyle Hurd
     *  Modified:    12/04/20
     *  Description: Constructor for a laser class which is passed in a laser for a laser sprite,
     *               then first loads in a laser sound file, and after that initializes five of
     *               these objects to a texture, scale and initializes the velocity to a constant
     *               laser object speed and sets a boolean fired variable for each of these objects
     *               to false initially.
     */
    Laser::Laser(const sf::Texture& tLaser) {

        buffer.loadFromFile("Resources/Sounds/Laser.wav");
        laserSound.setBuffer(buffer);
        for (int i = 0; i < 5; i++) {
            object[i].setTexture(tLaser);
            object[i].setScale(0.75, 0.75);
            velocity[i].x = laserSpeed;
            velocity[i].y = 0;
            fired[i] = false;
        }
    }

    Laser::~Laser() {}


    /* *
     *  Created by:  Justin Pilgrim
     *  Modified:    12/04/20
     *  Description: passed in the bird sprite and also a index number for the lazer object
     *               array. Checks to if a laser object is has currently not been fired and
     *               if the object has not then it will be set to the bird object's position
     *               and changes the object's correlating fired boolean variable to true.
     *
     */
    void Laser::shoot(Bird::BirdSprite& bird, int i) {
        // Laser reset or first shot
        if ((fired[i] == true && object[i].getPosition().x > WIDTH) || fired[i] == false) {
            laserSound.play();
            object[i].setPosition(bird.getPosition().x, bird.getPosition().y);
            object[i].move(velocity[i].x, velocity[i].y);
            fired[i] = true;
        }
    }

    /* *
     *  Created by:     Justin Pilgrim
     *  Modified:       12/04/20
     *  Description:    passed in a laser object array index number and checks to see if
     *                  the object's correlating fired boolean variable is fired is true
     *                  and if the laser object is not off the screen and if the object
     *                  and the fired variable meet this case then the laser object will
     *                  continue moving across the screen at a constant X velocity.
     */
    void Laser::moveLaser(int i) {
        // Ask others about doing the lose reset
        if (fired[i] == true && object[i].getPosition().x < WIDTH) {
            object[i].move(velocity[i].x, velocity[i].y);
        }
        else {
            fired[i] = false;
        }
    }


    /* *
     *  Created by: Justin Pilgrim
     *  Modified: 12/04/20
     *  Description: getSprite: returns a lazer Sprite Object.
     *               getPositionX: returns a lazer's X coordinate position.
     *               getPositionY: returns a lazer's Y coordinate position.
     */

    sf::Sprite Laser::getSprite(int i) {
        return object[i];
    }

    int Laser::getPositionX(int i) {
        return object[i].getPosition().x;
    }

    int Laser::getPositionY(int i) {
        return object[i].getPosition().y;
    }

}
