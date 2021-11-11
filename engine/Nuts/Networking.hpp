/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Networking.h
*/

#pragma once

#if defined(_WIN32)
#pragma warning(disable : 4091)
#endif //_WIN32

#include <SFML/Network.hpp>
#include <array>
#include <iostream>
#include <memory>

using ClientID = std::int32_t;
using MsgType = sf::Uint8;

enum class MsgTypes : sf::Uint8 {
    CLIENT_ID = 1,
    UDP_INFO,
    CLIENT_DISCONNECT,
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

// Router & Dispatcher
typedef class Dispatcher;

/**
 * @brief Router class must be inherited by a Dispatcher class
 * All message callbacks must be implemented in Dispatcher class
 * That's why Dispatcher is forward declared here
 */
class Router {
protected:
    typedef void (Dispatcher::*MessageFuncPtr)(sf::Packet& packet);
    std::array<MessageFuncPtr, MAX_MSG_TYPES> _remoteProcedureCalls {};

    void addCallback(MsgTypes rpcType, MessageFuncPtr callback)
    {
        _remoteProcedureCalls[MSG_TYPE(rpcType)] = callback;
    }

public:
};

/** TODO(adlan):
* ClientInterface
*/
class ClientInterface {
protected:
    std::shared_ptr<Connection> _clientConnection;
};

class ServerInterface {
protected:
    sf::TcpListener _listener;
    std::shared_ptr<Connection> _serverConnection;
};
