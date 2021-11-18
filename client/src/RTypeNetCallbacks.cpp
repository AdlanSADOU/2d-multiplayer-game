/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RtypeNetworkCallbacks.cpp
*/

#include "RType.hpp"

void RType::OnNetReceivedId(Event &event)
{
    sf::Packet packet = event.GetParam<sf::Packet>(0);
    ClientID   id;
    packet >> id;

    SetLocalClientId(id);

    sf::Packet udpInfoPacket;
    udpInfoPacket << Net::Events::CLIENT_UDP
                  << GetLocalClientId()
                  << Net::INetClient::GetLocalUdpPort();

    Net::INetClient::TcpSend(udpInfoPacket);

    sf::Packet lpacket;
    lpacket << Net::Events::MATCHM_INIT
            << GetLocalClientId();

    Net::INetClient::TcpSend(lpacket);
}

void RType::OnQuickPlayBtn(Event &event)
{
    /** TODO(adlan):
    * if already connected, just relaunch matchmaking
    */
    if (INetClient::IsConnected()) return;

    if (INetClient::Connect(sf::IpAddress::getLocalAddress(), 55001))
        _state = GameState::MATCHM;
}

void RType::OnNewClient(Event &event)
{
    sf::Packet packet = event.GetParam<sf::Packet>(0);
    ClientID   id;
    sf::Int32  gameId;

    packet >> id >> gameId;

    std::cout << "[Client]: Client ["
              << id
              << "] joined game ["
              << gameId
              << "]\n";
}

void RType::OnClientQuit(Event &event)
{
    sf::Packet packet = event.GetParam<sf::Packet>(0);
    ClientID   id;
    sf::Int32  gameId;

    packet >> id >> gameId;

    std::cout << "[Client]: Player [" << id
              << "] quit game [" << gameId << "]\n";
}

void RType::OnStartGame(Event &event)
{
    _state = GameState::GAME;
}