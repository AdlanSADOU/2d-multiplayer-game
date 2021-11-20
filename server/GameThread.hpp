/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** GameThread.hpp
*/

#pragma once

#include <thread>
#include <vector>
#include <Nuts/EcsCore/EventManager.h>

class GameThread
{
private:
    std::vector<std::shared_ptr<SClientComponent>> _clients;
    EventManager                                   _eventManager;

    std::int32_t  _gameId;
    sf::UdpSocket _socket;
    bool          _running = false;

public:
    GameThread()
    {
        _running = true;

        _eventManager.AddEventCallback(Net::Events::REMOTE_CLIENT_KEYS, BIND_CALLBACK(&GameThread::OnClientKeyEvent, this));
    };

    void Run(std::vector<std::shared_ptr<SClientComponent>> clients, std::int32_t gameId)
    {
        _clients = std::move(clients);
        _gameId  = gameId;

        _socket.bind(sf::Socket::AnyPort, sf::IpAddress::getLocalAddress());
        _socket.setBlocking(false);
        for (auto &client : _clients) {
            sf::Packet packet;

            packet << Net::Events::GAME_START;
            _socket.send(packet, client->ip, client->updPort);

            packet.clear();

            std::cout << "ThreadId[" << threadID() << "|port:" << _socket.getLocalPort() << "]: Launching game with "
                      << client->ip << ":" << client->updPort << "\n";

            packet << Net::Events::INITIAL_GAME_INFO;
            for (auto &client : _clients) {
                packet << client->id;
            }

            _socket.send(packet, client->ip, client->updPort);
        }

        while (_running) {
            receive();
        }
    }

    void receive()
    {
        sf::Packet remotePacket;
        EventType  type;

        sf::IpAddress remoteAddress;
        sf::Uint16    remotePort;

        sf::Socket::Status status = _socket.receive(remotePacket, remoteAddress, remotePort);
        if (status == sf::Socket::Done) {
            remotePacket >> type;
            Event remoteEvent(type);
            remoteEvent.SetParam<sf::Packet>(0, remotePacket);
            _eventManager.InvokeEvent(remoteEvent);
        }
    }

    void Broadcast(sf::Packet packet, ClientID ignoredClientId)
    {
        for (auto &client : _clients) {
            if (client->id != ignoredClientId) {
                _socket.send(packet, client->ip, client->updPort);
            }
        }
    }

    // relay key events to other clients
    void OnClientKeyEvent(Event &event)
    {
        sf::Packet inClientKeyPacket = event.GetParam<sf::Packet>(0);

        ClientID  clientId;
        sf::Int32 pressedKey;
        sf::Int32 releasedKey;

        inClientKeyPacket >> clientId >> pressedKey >> releasedKey;

        sf::Packet outClientKeyPacket;
        outClientKeyPacket << Net::Events::REMOTE_CLIENT_KEYS << clientId << pressedKey << releasedKey;
        Broadcast(outClientKeyPacket, clientId);

    }
};