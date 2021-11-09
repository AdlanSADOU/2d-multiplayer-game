/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Dispatcher.hpp
*/

#pragma once

#include "SClientManager.hpp"
#include <Nuts/Networking.hpp>
#include <cassert>

/** TODO(adlan):
* clas ServerDispatcher : public Dispatcher
*/
class Dispatcher {
private:
    typedef void (Dispatcher::*RemoteCallPtr)(sf::Packet& packet);
    std::array<RemoteCallPtr, MAX_MSG_TYPES> _remoteProcedureCalls {};
    std::shared_ptr<SClientManager> _clientManager {};
    std::shared_ptr<Connection> _serverConnection {};

    void addCallback(MsgTypes rpcType, RemoteCallPtr callback)
    {
        _remoteProcedureCalls[MSG_TYPE(rpcType)] = callback;
    }

public:
    Dispatcher(std::shared_ptr<SClientManager> clientManager, std::shared_ptr<Connection> serverConnection)
    {
        _clientManager = clientManager;
        _serverConnection = serverConnection;

        addCallback(MsgTypes::CLIENT_DISCONNECT, &Dispatcher::ClientDisconnect);
        addCallback(MsgTypes::CLIENTS_PRINT, &Dispatcher::ClientsPrint);
        addCallback(MsgTypes::UDP_INFO, &Dispatcher::ClientAddUdp);
    }

    bool Dispatch(sf::Packet& packet, SocketType sockType)
    {
        MsgType rpcType = -1;
        packet >> rpcType;

        assert(rpcType < MAX_MSG_TYPES && "MsgType non-existent\n");

        if (sockType == SocketType::Tcp)
            printf("[SERVER_TCP]: received MsgType[%d]\n", rpcType);
        else
            printf("[SERVER_UDP]: received MsgType[%d]\n", rpcType);

        (this->*(_remoteProcedureCalls[rpcType]))(packet);

        if (rpcType == MSG_TYPE(MsgTypes::CLIENT_DISCONNECT))
            return true;
        return false;
    }

    /**
     * @brief Sends the packet to all clients except the ignored one.
     * if no ClientID is specified packet will be sent to all clients by default
     *
     * @param packet packet to send
     * @param ClientID ignored client
     *
     */
    void Broadcast(sf::Packet& packet, ClientID ignoredClientId = -1)
    {
        for (auto& client : _clientManager->clients) {
            _serverConnection->UdpSend(packet, client.second.ip, client.second.updPort);
        }
    }

    void ClientDisconnect(sf::Packet& packet)
    {
        ClientID remoteId;
        packet >> remoteId;
        if (_clientManager->DisconnectClient(remoteId)) {
            sf::Packet ClientDisconnectedPacket;
            ClientDisconnectedPacket << MSG_TYPE(MsgTypes::CLIENT_DISCONNECT) << remoteId;
            Broadcast(ClientDisconnectedPacket, remoteId);
        }
    }

    void ClientAddUdp(sf::Packet& packet)
    {
        ClientID remoteId;
        sf::Uint16 udpPort;
        packet >> remoteId >> udpPort;

        _clientManager->AddClientUdpPort(udpPort, remoteId);

        sf::Packet p;
        p << MSG_TYPE(MsgTypes::UDP_INFO) << "connected";
    }

    void ClientsPrint(sf::Packet& packet)
    {
        _clientManager->PrintConnectedClients();
    }

    void ClientAddToLobby(sf::Packet& packet)
    {
    }
};
