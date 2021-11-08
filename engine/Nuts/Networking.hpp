/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Networking.h
*/

#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <memory>

using ClientID = sf::Int8;
using MsgType = sf::Uint8;

enum class MsgTypes : sf::Uint8 {
    CLIENT_ID = 1,
    CLIENT_DISCONNECT,
    CLIENT_UDP_INFO,
    CLIENTS_PRINT,
    LOBBY_LIST,
    LOBBY_CREATE,
    LOBBY_ID,
};

enum SocketType {
    Tcp,
    Udp
};

#define MAX_MSG_TYPES 64
#define MSG_TYPE(x) (static_cast<sf::Uint8>(x))

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

/** TODO(adlan):
* ClientInterface
*/
class ServerInterface {
private:
protected:
    sf::TcpListener _listener;
    std::shared_ptr<Connection> _serverConnection;
};
