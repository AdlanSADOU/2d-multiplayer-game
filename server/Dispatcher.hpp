/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Dispatcher.hpp
*/

#pragma once

#include "SClientManager.hpp"
#include <Nuts/Networking.hpp>
#include <array>
#include <cassert>

extern std::unique_ptr<SClientManager> _clientManager;
typedef void (*RemoteCallPtr)(sf::Packet& packet);

void ClientDisconnect(sf::Packet& packet)
{
    ClientID remoteId;
    packet >> remoteId;
    _clientManager->DisconnectClient(remoteId);
}

void ClientAddUdp(sf::Packet& packet)
{
    ClientID remoteId;
    sf::Uint16 udpPort;
    packet >> remoteId >> udpPort;

    _clientManager->AddClientUdpPort(udpPort, remoteId);
}

void ClientsPrint(sf::Packet& packet)
{
    _clientManager->PrintConnectedClients();
}

class Dispatcher {
private:
    std::array<RemoteCallPtr, 64> _remoteProcedureCalls {};

    void addCallback(ERpc rpcType, RemoteCallPtr callback)
    {
        _remoteProcedureCalls[RPC(rpcType)] = callback;
    }

public:
    void Init()
    {
        addCallback(ERpc::CLIENT_DISCONNECT, &ClientDisconnect);
        addCallback(ERpc::CLIENTS_PRINT, &ClientsPrint);
        addCallback(ERpc::CLIENT_UDP, &ClientAddUdp);
    }

    bool Dispatch(sf::Packet& packet)
    {
        Rpc rpcType = -1;

        packet >> rpcType;
        //assert(_remoteProcedureCalls.size() == 0 && "no procedures to call\n");
        _remoteProcedureCalls[rpcType](packet);

        if (rpcType == ERpc::CLIENT_DISCONNECT)
            return true;
        return false;
    }
};
