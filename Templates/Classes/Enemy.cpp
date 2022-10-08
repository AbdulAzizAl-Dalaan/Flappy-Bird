//
//  Laser.cpp
//  SFMLProject
//
//  Created by © Justin Pilgrim on 11/23/20.
//  Copyright  2020 Justin Pilgrim. All rights reserved.
//
//  Description
//
//  Class member functions for the Enemy class for the
//  Flappy Invanders game mode of the Flappy Bird game.
//

#include "Enemy.hpp"

namespace EnemySprite {

/* *
 *  Created by:  Justin Pilgrim
 *  Modified:    12/04/2020
 *  Description: The constructor initializes private member variables of the Enemy class.
 *               In order for the function to work properly a double type and a sf::Texture
 *               must be passsed into the function. The function returns nothing and only updates
 *               the private members of the object
 */
Enemy::Enemy(double speed, sf::Texture &image) {
    enemies.setTexture(image);
    enemies.setScale(0.2, 0.2);
    velocity.x = speed;
    velocity.y = 0;
    positionX = WIDTH;
    positionY = 0;
    hit = false;
    enemies.setPosition(WIDTH, 200);
}

/* *
 *  Created by:  Justin Pilgrim
 *  Modified:    12/04/2020
 *  Description: The destructor
 *                FREAKING OBLITERATES the object should it commit the sin of
 *                leaving its scope.
 */
Enemy::~Enemy() {}

/* *
 *  Created by:  Justin Pilgrim
 *  Modified:    12/04/2020
 *  Description: The member function sets the initial position of the enemy object
 *               or resets it to edge of the right screen at some random y coordinate
 *               if the enemy has not been deployed or if it was destroyed. The function
 *               requires not input and it does not return anything. Only the private
 *               members of the object are updated accordingly. It must have access
 *               to private members to work properly.
 */
void Enemy::enemyDeploy() {
    // Checking to see if the enemy is in play
    if (positionX == WIDTH && hit == false) {
        positionY = rand() % 800 + 100;
        enemies.setPosition(positionX, positionY);
    }
    // reset enemy
    else if (positionX < 0 || hit == true) {
        hit = false;
        positionY = rand() % 800 + 100;
        positionX = WIDTH;
        positionX += velocity.x;
    }
}

/* *
 *  Created by:  Justin Pilgrim
 *  Modified:    12/04/2020
 *  Description: The member function moves the enemy object as long as the enemy has
 *               not me destroyed.If the bool value hit is false then the enemy's position
 *               is updated to move left across the screen. The function returns nothing and
 *               only updates the private members of the object. It must have access to
 *               the private members or it will not work properly.
 */
void Enemy::enemyMove() {
    if (hit == false) { // If the enemy is not hit
        if (positionX >= 0 && positionX <= WIDTH) {
            positionX += velocity.x;
            enemies.setPosition(positionX, positionY);
        }
    }
}

/* *
 *  Created by:  Justin Pilgrim
 *  Modified:    12/04/2020
 *  Description: The getter function returns the sf::Sprite enemies which is used for
 *               drawing to the screen.The function must have access to variable
 *               enemies in order to work properly.
 */
sf::Sprite Enemy::getSprite() {
    return enemies;
}

/* *
 *  Created by:  Justin Pilgrim
 *  Modified:    12/04/2020
 *  Description: The member function determines if an enemy object is destroyed and then resets them.
 *               The function returns a bool value true if the enemy was hit or false if it is the
 *               opposite. The function checks the position of the enemy object with a laser object.
 *               If they overlap then the enemy is considered hit and the private members of enemy are
 *               update accordingly. Also the +35 and -35 for enemy position are meant to get a range
 *               of values as opposed to simply the enemy's center. It also makes the hit box bigger
 *               for the enemy.
 */
bool Enemy::enemyDestroyed(int l, LaserSprite::Laser &laser) {
    // Check x coordinates
    if (laser.getPositionX(l) >= (enemies.getPosition().x - 35) &&
        laser.getPositionX(l) <= (enemies.getPosition().x + 35)) {
        // Check y coordinates
        if (laser.getPositionY(l) >= (enemies.getPosition().y - 35) && laser.getPositionY(l) <= (enemies.getPosition().y + 35)) {
            hit = true;
            enemyDeploy();
            return true;
        }
    }
    return false;
}

/* *
 *  Created by:  Justin Pilgrim
 *  Modified:    12/04/2020
 *  Description: The getter function returns the sf::Vector2f of the enemy object in order
 *               to get the position of the enemy object which will be used in other functions
 *               for computation. The function must have access to variable enemies in order to work properly.
 */
sf::Vector2f Enemy::getPosition() {
    return enemies.getPosition();
}

/* *
 *  Created by:  Justin Pilgrim
 *  Modified:    12/04/2020
 *  Description: The member function resets the enemy object's position and private values if the player has
 *               died. The enemies are reset to the right corner of the window and their hit value is updated
 *               to read false.
 */
void Enemy::enemyReset() {
    if (currentState == LOSE) {
        hit = false;
        positionX = WIDTH;
        enemies.setPosition(WIDTH, 0);
    }
}

}
