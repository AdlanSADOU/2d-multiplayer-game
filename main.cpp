/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** main
*/

#include <iostream>
#include <string> // required on windows for std::to_string(...)
#include <SFML/Graphics.hpp>
#include "Pig.hpp"

int main(void)
{
    Pig peppa(10);
    std::cout << std::to_string(peppa.GetPigSize()) << std::endl;

    sf::Window window(sf::VideoMode(800, 600), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}
