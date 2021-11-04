#pragma once

#include "SClient.hpp"

class SClientManager
{
private:

std::vector<SClient> clients;
std::vector<sf::TcpSocket *> clientSockets;

public:
	SClient &GetClientById() {
        
    };

};
