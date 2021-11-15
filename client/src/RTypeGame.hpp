/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RTypeGame
*/

#pragma once

#include <SFML/Graphics.hpp>

class RTypeGame {
    enum PlayerColor {
        BLUE = 0,
        RED,
        YELLOW,
        GREEN
    };

public:
    RTypeGame();
    ~RTypeGame();

    void Draw(sf::RenderWindow window);

protected:
private:
};
