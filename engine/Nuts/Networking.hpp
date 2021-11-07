/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Networking.h
*/

#pragma once

#include <SFML/Network.hpp>
#include <iostream>

using ClientID = sf::Uint8;
using Rpc = sf::Uint8;

enum ERpc {
    CLIENT_CONNECT = 1,
    CLIENT_DISCONNECT,
    CLIENT_UDP,
    CLIENTS_PRINT,
    LOBBY_CREATE,
    LOBBY_ID,
};

enum SocketType {
    Tcp, ///< TCP protocol
    Udp ///< UDP protocol
};

#define MAX_RPC 64
#define RPC(x) (static_cast<sf::Uint8>(x))

class Connection {
private:
    SocketType _type;
    std::shared_ptr<sf::UdpSocket> _udpSock;
    std::shared_ptr<sf::TcpSocket> _tcpSock;
    sf::IpAddress _ipAdress;
    sf::Uint16 _port;

public:
    ~Connection()
    {
        _tcpSock->disconnect();
    }

    void AssignTcpSocket(sf::TcpSocket* socket)
    {
        _tcpSock.reset(socket);
    }

    void TcpConnect(sf::IpAddress remoteIp, sf::Uint16 remotePort)
    {
        sf::Socket::Status status;
        if (_tcpSock->connect(remoteIp, remotePort) != sf::Socket::Status::Done)
            std::cerr << "ERROR:TCP: unable to connect\n";
    }
    void UdpBind(sf::Uint16 port, sf::IpAddress ip)
    {
        _udpSock = std::make_shared<sf::UdpSocket>();
        sf::Socket::Status status;
        if (_udpSock->bind(port, ip) != sf::Socket::Status::Done)
            std::cerr << "ERROR:UDP: unable to connect\n";
    }
    void UdpSetBlocking(bool value)
    {
        _udpSock->setBlocking(value);
    }
    void TcpSetBlocking(bool value)
    {
        _tcpSock->setBlocking(value);
    }

    sf::Socket::Status Send(sf::Packet& packet)
    {
        sf::Socket::Status status;
        if ((status = _tcpSock->send(packet)) != sf::Socket::Status::Done)
            std::cerr << "ERROR:TCP: unable to send\n";
    }

    sf::Socket::Status UdpSend(sf::Packet& packet, sf::IpAddress& remoteIp, sf::Uint16 remotePort)
    {
        sf::Socket::Status status;
        if ((status = _udpSock->send(packet, remoteIp, remotePort)) != sf::Socket::Status::Done)
            std::cerr << "ERROR:UDP: unable to send\n";
        return status;
    }

    sf::Socket::Status UdpReceive(sf::Packet& packet, sf::IpAddress& remoteIp, sf::Uint16& remotePort)
    {
        sf::Socket::Status status;
        (status = _udpSock->receive(packet, remoteIp, remotePort));
        // std::cerr << "ERROR:UDP: unable to receive\n";
        return status;
    }
};

class ServerInterface {
private:
protected:
    sf::TcpListener _listener;
    std::shared_ptr<Connection> _serverConnection;
};
