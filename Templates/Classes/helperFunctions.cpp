//
//  helperFunctions.cpp
//  Flappy Bird
//
//  Created by Kyle Hurd and Abdul Aziz Al-Dalaan on 11/15/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//
//  The extern int is declared here to create a global variable for all the
//  classes and Scenes to view to check the current state of the game. Depending
//  on the state, the classes will compare their state with the global state
//  to ensure the functionality is acting as it should. More information of the
//  other functions is written in the function definition.
//

#include "helperFunctions.hpp"

// Global Declaration
int currentState = LOSE;
GameData playerStats;
GameData highScores[10];

const int laserSpeed = 50;

// **Function Definitions** //
/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/28/2020
 *  Description: print() behaves much like the function
 *               from Python, and was created to try and clean
 *               up the look of the code. You can add multiple
 *               elements by appending them via a '+'.
 *               Ex. print("Hello " + name + "!");
 *               Default output is cout, but can be outputted to
 *               a file or other source by adding the location
 *               as a second parameter.
 *               Ex.
 *               std::fstream outfile;
 *               openOutFile(outfile, "path/to/file.txt");
 *               print("Output to fstream", outfile);
 */
void print(std::string n, std::ostream &output) {
    output << n << std::endl;
}

/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/28/2020
 *  Description: Opens an fstream type variable in input
 *               mode from the name of the file provided
 *               by the string s.
 *
 *               Ex.
 *               std::fstream infile;
 *               openInFile(infile, "./path/to/file.txt");
 */
void openInFile(std::fstream &file, std::string s) {
    
    file.open(s, std::ios::in);
    
    if (file.is_open()) print(s + " opened successfully.");
    else                print(s + " could not be opened. Cannot read data.");
}

/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/28/2020
 *  Description: Opens an fstream type variable in output
 *               mode from the file name provided by the string
 *               s.
 *
 *               Ex.
 *               std::fstream outfile;
 *               openOutFile(outfile, "./path/to/file.txt");
 */
void openOutFile(std::fstream &file, std::string s) {
    
    file.open(s, std::ios::out);
    
    if (file.is_open()) print(s + " opened successfully.");
    else                print(s + " could not be opened. Cannot write data.");
}

/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/28/2020
 *  Description: Converts an integer to a string. For example,
 *               if int 42 is passed in, '42' as a string will
 *               be returned.
 */
std::string numToString(int num) {
    std::ostringstream ss;
    ss << num;
    return ss.str();
}

/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/28/2020
 *  Description: Loads in the high score data and players last username
 *               into the global GameData variables playerStats and array
 *               highScores (current size is ten).
 */
void getHighScoreData(std::fstream &infile) {
    // Get the first line
    std::string temp;
    std::getline(infile, temp); // Name
    std::getline(infile, playerStats.username);
    std::getline(infile, temp); //UserName,Score
    
    // Get Proceeding Lines
    int i = 0;
    while (!infile.eof() && i < 10) {
        std::getline(infile, highScores[i].username, ',');
        std::getline(infile, temp, '\n');
        highScores[i].currentScore = stoi(temp); // C++11
        // infile >> highScores[i].currentScore ;
        i++;
    }
}

/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/28/2020
 *  Description: Sorts the global GameData array 'highScores' using
 *               bubble sort. The alogrithm sorts from largest to smallest.
 */
void bubbleSortGameData() {
    for (int i = 0; i < 10; ++i) {
        bool flag = true;
        for (int j = 0; j < 9 - i; ++j) {
            if (highScores[j].currentScore < highScores[j + 1].currentScore) {
                GameData temp = highScores[j];
                highScores[j] = highScores[j+1];
                highScores[j+1] = temp;
                flag = true;
            }
        }
        if (flag == false) {
            break;
        }
    }
}

/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/28/2020
 *  Description: Writes the updated information (players current username,
 *               and the high scores) into the designated outfile by adding a new high
 *               score if needed to the global highScores data and sorting the array.
 *               The outfile should already be opened when passed into the function.
 *               The function does not close outfile after writing.
 */
void updateHighScoreData(std::fstream &outfile) {
    // Condition is that global GameData for high scores is already filled.
    print("Name\n" + playerStats.username + "\nUserName,Score", outfile);
    if (playerStats.currentScore > highScores[9].currentScore) {
        highScores[9] = playerStats;
    }
    bubbleSortGameData();
    for (int i = 0; i < 10; i++) {
        print(highScores[i].username + "," + numToString(highScores[i].currentScore), outfile);
    }
}

/* *
 *  Created by:  Abdul Aziz Al-Dalaan
 *  Modified:    11/28/2020
 *  Description: Checks if a collision between the pipes and the bird has taken place.
 *               Returns true if there has been a collision and false otherwise.
 *
 *               The function checks three locations:
 *                      - A head on collision of the top pipe (first if statement)
 *                      - The inner bounds of the top and bottom pipe (second if statement)
 *                      - A head on collision of the bottom pipe (third if statement)
 */
bool checkCollision(sf::Vector2f birdTop, sf::Vector2f birdRight,
                        sf::Vector2f holePosition, sf::Vector2f holeSize) {

    sf::Vector2f birdLeft(birdTop.x - (birdRight.x - birdTop.x), birdRight.y);
    sf::Vector2f birdBottom(birdTop.x, (birdRight.y + (birdRight.y - birdTop.y)));

    if (((birdRight.x > holePosition.x && birdRight.x < holePosition.x + holeSize.x) || // TOP
        (birdLeft.x > holePosition.x && birdLeft.x < holePosition.x + holeSize.x)) &&
        (birdRight.y < holePosition.y || birdLeft.y < holePosition.y)) {
        return true;
    }
    else if (((birdTop.x > holePosition.x && birdTop.x < holePosition.x + holeSize.x) ||  // MIDDLE
        (birdBottom.x > holePosition.x && birdBottom.x < holePosition.x + holeSize.x)) &&
        (birdTop.y < holePosition.y || birdBottom.y > holePosition.y + holeSize.y)) {
           return true;
    }
    else if (((birdLeft.x > holePosition.x && birdLeft.x < holePosition.x + holeSize.x) || // BOTTOM
             (birdRight.x > holePosition.x && birdRight.x < holePosition.x + holeSize.x)) &&
              (birdLeft.y > holePosition.y + holeSize.y || birdRight.y > holePosition.y + holeSize.y)) {

         return true;
    }

    return false;
}

/* *
 *  Created by:  Justin Pilgrim
 *  Modified:    12/04/2020
 *  Description: <insert>
 */
bool checkCollision(sf::Vector2f birdTop, sf::Vector2f birdRight, sf::Vector2f enemyPosition) {

    sf::Vector2f birdLeft(birdTop.x - (birdRight.x - birdTop.x), birdRight.y);
    sf::Vector2f birdBottom(birdTop.x, (birdRight.y + (birdRight.y - birdTop.y)));

    if (birdTop.x >= (enemyPosition.x - 35) && birdTop.x <= (enemyPosition.x + 35) && birdTop.y >= (enemyPosition.y - 35) && birdTop.y <= (enemyPosition.y + 35))//Top
    {
        return false;
    }
    else if (birdBottom.x >= (enemyPosition.x - 35) && birdBottom.x <= (enemyPosition.x + 35) && birdBottom.y >= (enemyPosition.y - 35) && birdBottom.y <= (enemyPosition.x + 35))//Bottom
    {
        return false;
    }
    else if (birdLeft.x >= (enemyPosition.x - 35) && birdLeft.x <= (enemyPosition.x + 35) && birdLeft.y >= (enemyPosition.y - 35) && birdLeft.y <= (enemyPosition.x + 35))//Left
    {
        return false;
    }
    
    return true;
}

/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/28/2020
 *  Description: An overloaded == operator to check if two Vector2f
 *               are identical or not. Returns true if same, false
 *               otherwise.
 */
bool operator== (const sf::Vector2f &lhs, const sf::Vector2f &rhs) {
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}
