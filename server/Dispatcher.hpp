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

class Dispatcher {
private:
    typedef void (Dispatcher::*RemoteCallPtr)(sf::Packet& packet);
    std::array<RemoteCallPtr, 64> _remoteProcedureCalls {};
    std::shared_ptr<SClientManager> _clientManager {};
    std::shared_ptr<Connection> _serverConnection {};

    void addCallback(ERpc rpcType, RemoteCallPtr callback)
    {
        _remoteProcedureCalls[RPC(rpcType)] = callback;
    }

public:
    Dispatcher(std::shared_ptr<SClientManager> clientManager, std::shared_ptr<Connection> serverConnection)
    {
        _clientManager = clientManager;
        _serverConnection = serverConnection;

        addCallback(ERpc::CLIENT_DISCONNECT, &Dispatcher::ClientDisconnect);
        addCallback(ERpc::CLIENTS_PRINT, &Dispatcher::ClientsPrint);
        addCallback(ERpc::CLIENT_UDP, &Dispatcher::ClientAddUdp);
    }

    bool Dispatch(sf::Packet& packet)
    {
        Rpc rpcType = -1;

        packet >> rpcType;
        (this->*(_remoteProcedureCalls[rpcType]))(packet);

        if (rpcType == RPC(ERpc::CLIENT_DISCONNECT))
            return true;
        return false;
    }

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

        sf::Packet p;
        p << RPC(ERpc::CLIENT_UDP) << "connected";
    }

    void ClientsPrint(sf::Packet& packet)
    {
        _clientManager->PrintConnectedClients();
    }

    void ClientAddToLobby(sf::Packet& packet)
    {
    }
};
