/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Sclient.hpp
*/

#include <Nuts/Networking.hpp>

class SClient {
public:
    sf::TcpSocket* socket;
    ClientID uuid;
    bool registered;
    bool IsInLobby;
    std::uint8_t lobbyID;
};
