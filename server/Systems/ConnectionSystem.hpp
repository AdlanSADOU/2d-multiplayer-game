/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** ConnectionSystem.hpp
*/

#pragma once

#include "Components/Components.hpp"
#include <iostream>
#include <vector>

class ConnectionSystem : public System {
private:
    ConnectionComponent _conn;
    std::shared_ptr<sf::TcpSocket> _tmpSocket;

public:
    int Init(unsigned short port, const sf::IpAddress& address = sf::IpAddress::Any)
    {
        std::set<Entity>::iterator entity = _entities.find(0);
        _conn = scene.GetComponent<ConnectionComponent>(*entity);

        _conn.listener = std::make_shared<sf::TcpListener>();
        _conn.listener->setBlocking(false);

        if (_conn.listener->listen(port, address) != sf::Socket::Status::Done) {
            std::cout << "[Server]: Failed to listen on " << address << ":" << port << std::endl;
            return -1;
        }

        _conn.isRunning = true;
        std::cout << "[Server]: Server running on " << address << ":" << port << std::endl;

        _conn.udpSock = std::make_shared<sf::UdpSocket>();
        if (_conn.udpSock->bind(port + 1, address) != sf::Socket::Done) {
            std::cout << "[Server]: UDP socket failed to bind on " << address << ":" << port << std::endl;
        }

        _conn.port = port + 1;
        std::cout << "[Server]: UDP socket bound on " << address << ":" << port + 1 << std::endl;

        _tmpSocket = std::make_shared<sf::TcpSocket>();

        return 0;
    }

    void Accept()
    {
        if (_conn.listener->accept(*_tmpSocket) == sf::Socket::Done) {
            std::cout << "connection request\n";

            Event clienConnectedEvent(Events::Net::CLIENT_CONNECT);
            clienConnectedEvent.SetParam<std::shared_ptr<sf::TcpSocket>>(0, _tmpSocket);
            scene.InvokeEvent(clienConnectedEvent);
        }
    }
};
