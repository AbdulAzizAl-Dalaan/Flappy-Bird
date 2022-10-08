//
//  CreditScene.cpp
//  FlappyBird
//
//  Created by Kyle Hurd on 12/3/20.
//  Copyright © 2020 Kyle Hurd. All rights reserved.
//

#include "CreditScene.hpp"


namespace CreditScene {
    void credits(sf::RenderWindow& window)
    {
        print("Entering CreditScene");

        sf::Texture BackgroundTexture;
        if (!BackgroundTexture.loadFromFile("Resources/Sprites/PixeledMenuWSU1.jpg")) {
            print("Could not load PixeledMenuWSU1.jpg from file");
        }
        sf::Sprite Background(BackgroundTexture);
        Background.setScale(1.03, 1.04);
        Background.setPosition(-4, 0);
        sf::Font textfont;
        if (!textfont.loadFromFile("Resources/Fonts/sansation.ttf")) {
            print("Could not load sansation font from file");
        }

        int creditX = WIDTH / 2;
        int mainTitleY = 1100;


        sf::Text mainTitle;
        mainTitle.setString("THE FLAPPIEST BIRD");
        mainTitle.setFont(textfont);
        mainTitle.setCharacterSize(75);
        mainTitle.setFillColor(sf::Color::Yellow);
        mainTitle.setOutlineThickness(10);
        mainTitle.setOutlineColor(sf::Color::Black);
        mainTitle.setOrigin(mainTitle.getLocalBounds().left + mainTitle.getLocalBounds().width / 2.0f,
            mainTitle.getLocalBounds().top + mainTitle.getLocalBounds().height / 2.0f);
        mainTitle.setPosition(creditX, mainTitleY);

        int createdByYpos = mainTitleY + 150;
        sf::Text created;
        created.setString("Created by");
        created.setFont(textfont);
        created.setCharacterSize(50);
        created.setFillColor(sf::Color::Yellow);
        created.setOutlineThickness(10);
        created.setOutlineColor(sf::Color::Black);
        created.setOrigin(created.getLocalBounds().left + created.getLocalBounds().width / 2.0f,
            created.getLocalBounds().top + created.getLocalBounds().height / 2.0f);
        created.setPosition(creditX, createdByYpos);

        sf::Text creditNames[4];
        int nameYposition[4];
        std::string names[4] = { "Kyle Hurd", "Justin Pilgrim", "William Holbert", "AbdulAziz Al-Dalaan" };
        for (int i = 0; i < 4; i++) {
            creditNames[i].setString(names[i]);
            creditNames[i].setFont(textfont);
            creditNames[i].setCharacterSize(30);
            creditNames[i].setFillColor(sf::Color::Yellow);
            creditNames[i].setOutlineColor(sf::Color::Black);
            creditNames[i].setOutlineThickness(7);
            creditNames[i].setOrigin(creditNames[i].getLocalBounds().left + creditNames[i].getLocalBounds().width / 2.0f,
                creditNames[i].getLocalBounds().top + creditNames[i].getLocalBounds().height / 2.0f);
            nameYposition[i] = createdByYpos + (i + 1) * 150;
            creditNames[i].setPosition(creditX, nameYposition[i]);
        }

        int finalPromptYpos = nameYposition[3] + 300;
        sf::Text finalPrompt;
        finalPrompt.setString("Flappy Bird shall return");
        finalPrompt.setFont(textfont);
        finalPrompt.setCharacterSize(25);
        finalPrompt.setFillColor(sf::Color::Yellow);
        finalPrompt.setOutlineThickness(5);
        finalPrompt.setOutlineColor(sf::Color::Black);
        finalPrompt.setOrigin(finalPrompt.getLocalBounds().left + finalPrompt.getLocalBounds().width / 2.0f,
            finalPrompt.getLocalBounds().top + finalPrompt.getLocalBounds().height / 2.0f);
        created.setPosition(creditX, finalPromptYpos);

        // Modifying Window
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
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
                        if (event.key.code == sf::Keyboard::M) {
                            print("M key pressed.");
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

            mainTitle.setPosition(creditX, mainTitleY -= 1);
            created.setPosition(creditX, createdByYpos -= 1);
            finalPrompt.setPosition(creditX, finalPromptYpos -= 1);

            if (finalPromptYpos == -15) {
                currentState = MENU;
                return;
            }

            // Drawing to Window
            window.clear();
            window.draw(Background);
            window.draw(mainTitle);
            window.draw(created);
            for (int i = 0; i < 4; i++) {
                creditNames[i].setPosition(creditX, nameYposition[i] -= 1);
                window.draw(creditNames[i]);
            }
            window.draw(finalPrompt);
            window.display();
        }
    }
}
