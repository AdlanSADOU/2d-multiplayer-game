/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** main.cpp
*/

#include "src/RType.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

Scene scene;

int main()
{
    RType rtype;
    rtype.Init();
    rtype.Run();

    return 0;
}