#pragma once

#include "SClient.hpp"
#include <assert.h>
#include <unordered_map>

class SClientManager {
private:
    ClientID _clientId = 0;

public:
    std::unordered_map<ClientID, SClient> clients {};
    void RegisterClient(sf::TcpSocket* socket);
    bool DisconnectClient(ClientID remoteId);
    void PrintConnectedClients();
};
