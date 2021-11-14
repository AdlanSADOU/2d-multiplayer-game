/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Components.hpp
*/

#pragma once

#include <Nuts/Networking.hpp>

struct SClientComponent {
    std::shared_ptr<sf::TcpSocket> tcpSock;
    sf::Uint16 updPort;
    sf::IpAddress ip;
    ClientID id;
    std::uint8_t gameId;
    bool isConnected = false;
    bool isGame = false;
};

struct ConnectionComponent {
    std::shared_ptr<sf::TcpListener> listener;
    std::shared_ptr<sf::UdpSocket> udpSock;
    std::shared_ptr<sf::TcpSocket> tcpSock;
    sf::IpAddress ipAdress;
    sf::Uint16 port;
    bool isConnected; // unused by server
    bool isRunning; // unused by client
};
