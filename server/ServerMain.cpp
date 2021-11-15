/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** ServerMain.cpp
*/

#include "EcsServer.hpp"

int main(int argc, char const *argv[])
{
    EcsServer server;

    server.Init();
    server.Start(55001, sf::IpAddress::getLocalAddress());

    return 0;
}
