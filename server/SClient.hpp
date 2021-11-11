/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Sclient.hpp
*/

#pragma once

#include <Nuts/Networking.hpp>

class SClient {
public:
    sf::TcpSocket* tcp;
    sf::Uint16 updPort;
    sf::IpAddress ip;
    ClientID uuid;
    bool connected;
    bool IsInLobby;
    std::uint8_t lobbyID;
};
