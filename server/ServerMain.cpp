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
    sf::Uint16 port = 55001;

    server.Init();
    server.Start(port, sf::IpAddress::getLocalAddress());


    return 0;
}


// int Oldmain()
// {
//     Server server;

//     server.Init();
//     server.Listen(55001);

//     sf::Clock testClock;
//     sf::Time acc;
//     sf::Time dt;

//     while (server.IsRunning()) {
//         // clock.restart() gives the time between each iteration
//         // so its a deltatime already
//         sf::Time dt = testClock.restart();
//         acc += dt;

//         if (acc.asSeconds() >= 1 / 30.f) { // run for 30 FPS
//             server.Accept();
//             server.Receive();
//             acc = acc.Zero;
//         }
//     }

//     server.ShutDown();
//     return 0;
// }
