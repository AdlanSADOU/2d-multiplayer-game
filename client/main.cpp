
#include <SFML/Graphics.hpp>
#include <Nuts.h>
#include <iostream>
#include <bitset>
#include <cassert>

int main()
{

    Nuts nuts;
    nuts.InitWindow("test window", 400, 200);

    while (nuts.IsRunning())
    {
        nuts.HandleInput();

        nuts.Clear();

        if (nuts.GetKeyDown(sf::Keyboard::Q))
            printf("WORKING !!\n");

        nuts.Present();
    }

    return 0;
}