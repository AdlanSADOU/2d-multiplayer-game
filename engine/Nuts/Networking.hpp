/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Networking.h
*/

#pragma once

#ifdef _WIN32
#pragma warning(disable : 4091)
#define threadID __threadid
#endif

#ifdef __unix
#define threadID __gthread_t
#endif

#define NET_LOG 0

#include <SFML/Network.hpp>
#include <array>
#include <iostream>
#include <memory>
#include <string>

#include <thread>
#include <mutex>

#define MUGUARD(my_mutex) noexcept(std::lock_guard<std::mutex>(my_mutex))

#include "EcsCore/Event.hpp"
#include "EcsCore/Scene.hpp"

#include <type_traits>

using ClientID = sf::Int32;

#define MAX_CLIENTS 4

extern Scene scene;

namespace Net {

    /**
     * @brief Utility namespace representing all the networking events that can occurs between the server and the client.
     *
     */

    enum Events
    {
        CLIENT_CONNECT = 1000,
        CLIENT_DISCONNECT,
        CLIENT_QUIT,
        CLIENT_ID,
        CLIENTS_PRINT,
        CLIENT_UDP,
        CLIENT_UPDATE_PACKETS,

        MONSTER_DESTROYED,
        MONSTER_UPDATE_POS,
        PLAYER_UPDATE_SCORE,

        NEW_CLIENT,
        UDP_OK,
        MATCHM_INIT,
        MATCHM_OK,
        MATCHM_PLAY,
        GAMEID,
        GAMEID_OK,
        INITIAL_GAME_INFO,
        GAME_START,

    };

    /**
     * @brief Networking instance of a Client.
     * The client is represented by two networking packet type : TCP & UDP. It stores the IP address & UDP port of both game & server. It is represented by a client ID, and a current state, to check is the user is connected to the server or not.
     */
    class INetClient {
    private:
        std::thread *th_udp_receive;
        std::mutex   _udpSocket_mutex;

        sf::TcpSocket  _tcp_socket;
        sf::UdpSocket *_udp_socket;

        sf::IpAddress _remote_game_ip;
        sf::Uint16    _remote_game_udp_port;

        sf::IpAddress _remote_server_ip;
        sf::Uint16    _remoteServerPort;

        sf::Clock _clock;
        sf::Time  _acc;
        sf::Time  _dt;

        ClientID _client_id    = -1;
        bool     _isConnected = false;

        /**
         * @brief Receive the incoming packet from the TCP socket, and invoke the attached event.
         *
         */
        void TcpReceive()
        {
            sf::Packet packet;

            MUGUARD(_udpSocket_mutex);
            if (_tcp_socket.receive(packet) == sf::Socket::Done) {
                EventType type;
                packet >> type;

                Event event(type);
                event.SetParam<sf::Packet>(0, packet);
                scene.InvokeEvent(event);
            }
        }

        /**
         * @brief Receive the incoming packet from the UDP socket, and invoke the attached event.
         *
         */
        void UdpReceive()
        {
            while (1) {
                sf::Socket::Status status = {};
                sf::Packet         packet = {};
                sf::Uint16         tmpUdp = 0;

                static std::uint64_t lastSequenceNumber = 0; // todo: packet sequence
                                                             // std::uint64_t sequenceNumber = 0;

                if ((status = _udp_socket->receive(packet, _remote_server_ip, tmpUdp)) == sf::Socket::Done) {

                    EventType type {};
                    packet >> type;
                    // packet >> sequenceNumber;

                    _remote_game_udp_port = tmpUdp;

                    Event event(type);
                    event.SetParam<sf::Packet>(0, packet);
                    scene.InvokeEvent(event);
                }

                if (status == sf::Socket::Partial)
                    std::cerr << "[Net]: Received partial data\n";
            }
        }

    public:
        /**
         * @brief Construct a new INetClient object
         *
         */
        INetClient() {};

        /**
         * @brief Disconnect the client from the tcp socket before destroying it.
         *
         */
        ~INetClient()
        {
            _tcp_socket.disconnect();
        }

        /**
         * @brief Return the id of the current client.
         *
         * @return ClientID
         */
        ClientID GetLocalClientId() const
        {
            return _client_id;
        }

        /**
         * @brief Return the port to which the UDP socket is bound locally
         *
         * @return sf::Uint16 if bound to a port, 0 otherwise
         */
        sf::Uint16 GetLocalUdpPort() const
        {
            return _udp_socket->getLocalPort();
        }

        /**
         * @brief Return IP address of the remote server.
         *
         * @return sf::IpAddress
         */
        sf::IpAddress GetRemoteServerIp() const
        {
            return _remote_server_ip;
        }

        /**
         * @brief Return the port the server is bound to.
         *
         * @return sf::Uint16
         */
        sf::Uint16 GetRemoteServerPort() const
        {
            return _remoteServerPort;
        }

        /**
         * @brief Return the connection status of the client.
         *
         * @return True if the client is connected, False otherwise.
         */
        bool IsConnected() const
        {
            return _isConnected;
        }

        /**
         * @brief Set the id of the client.
         *
         * @param id client id
         */
        void SetLocalClientId(ClientID id)
        {
            _client_id = id;
        }

        /**
         * @brief Receive packets from both TCP & UDP sockets.
         *
         */
        void Update()
        {
            _dt = _clock.restart();
            _acc += _dt;

            this->TcpReceive();
        }

        sf::Time GetAccumulatorTime()
        {
            return _acc;
        }

        void ResetAccumulatorTime()
        {
            _acc = _acc.Zero;
        }

        /**
         * @brief Connect the client to the server's Ip adress and port.
         *
         * @param serverIp Ip address of the server.
         * @param serverPort Port where the server is bound to.
         * @return True if the client has successfully connected, False if the user has failed connection to TCP socket or UDP socket.
         */
        bool Connect(sf::IpAddress serverIp, sf::Uint16 serverPort)
        {
            if (_tcp_socket.connect(serverIp, serverPort) != sf::Socket::Done) {
                std::cerr << "[Net]: Failed to connect to ["
                          << serverIp << ":"
                          << serverPort << "]\n";
                return false;
            }

            _remote_server_ip   = serverIp;
            _remoteServerPort = serverPort;
            _remote_game_ip     = serverIp;
            // _remote_game_udp_port = serverPort + 1;

            _udp_socket = new sf::UdpSocket();
            if (_udp_socket->bind(sf::Socket::AnyPort, sf::IpAddress::getLocalAddress()) != sf::Socket::Done) {
                std::cerr << "[Net]: Failed to connect to ["
                          << serverIp << ":"
                          << serverPort << "]\n";
                return false;
            }

            _tcp_socket.setBlocking(false);
            _udp_socket->setBlocking(false);
            _isConnected = true;

            std::cout << "[Net]: Connected to ["
                      << serverIp << ":"
                      << serverPort << "]\n";

            // sf::UdpSocket *_udp_socket, sf::IpAddress _remote_server_ip, sf::Uint16 *_remote_game_udp_port
            th_udp_receive = new std::thread(&INetClient::UdpReceive, this);

            return true;
        }

        /**
         * @brief Disconnect the client from the Tcp socket, if connected.
         *
         */
        void Disconnect()
        {
            if (_isConnected)
                _tcp_socket.disconnect();
            th_udp_receive->join();
        }

        /**
         * @brief Send a packet through the Tcp socket.
         * If the client is not connected, this function has no effect. Display an error in the terminal if it fails.
         * @param packet Packet to send.
         */
        void TcpSend(sf::Packet &packet)
        {
            if (!_isConnected) return;

            if (_tcp_socket.send(packet) != sf::Socket::Done) {
                std::cerr << "[Net-TCP]: Failed to send packet to [" << _tcp_socket.getRemoteAddress() << ":" << _tcp_socket.getRemotePort() << "\n";
            }
        }

        /**
         * @brief Send a packet through the Udp socket.
         * Displays an error in the output if it fails.
         * @param packet Packet to send.
         */
        void UdpSend(sf::Packet &packet)
        {
            if (!_isConnected) return;
            sf::Socket::Status status;

            if ((status = _udp_socket->send(packet, _remote_game_ip, _remote_game_udp_port)) != sf::Socket::Done) {
                std::cerr << "[Net-UDP]: Failed to send packet to [" << _remote_game_ip << ":" << _remote_game_udp_port << "\n";
            }
            if (status == sf::Socket::Partial)
                std::cerr << "[Net-UDP]: Sent partial data\n";
        }

        /**
         * @brief Set both Ip address & Udp port of the game.
         *
         * @param gameIp Ip address of the game.
         * @param gamePort Port where the game if bound to.
         */
        void SetRemoteGameUdpEndpoint(sf::IpAddress &gameIp, sf::Uint16 gamePort)
        {
            std::cerr << "[Net-UDP]: SetRemoteGameUdpEndpoint to [" << gameIp << ":" << gamePort << "\n";
            _remote_game_ip      = gameIp;
            _remote_game_udp_port = gamePort;
        }
    };
}
