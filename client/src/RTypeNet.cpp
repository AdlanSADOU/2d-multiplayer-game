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
    auto &mmPlayers = _matchMaking.GetPlayers();
    mmPlayers[id % MAX_CLIENTS].SetID(id);
    mmPlayers[id % MAX_CLIENTS].SetState(RTypeMMPlayer::READY);

    _matchMaking._localClientId = id;
    _matchMaking._isInitiated   = true;

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

    while (!packet.endOfPacket()) {
        ClientID tmpId;
        packet >> tmpId;

        std::cout << "[Client]: Client ["
                  << tmpId
                  << "] joined matchmaking "
                  << "]\n";

        auto &mmPlayers = _matchMaking.GetPlayers();
        mmPlayers[tmpId % MAX_CLIENTS].SetID(tmpId);
        mmPlayers[tmpId % MAX_CLIENTS].SetState(RTypeMMPlayer::READY);
    }
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
    sf::Packet packet   = event.GetParam<sf::Packet>(0);
    sf::Uint16 gamePort = 0;
    sf::Uint32 gameIp   = 0;

    packet >> gameIp >> gamePort;

    _state = GameState::GAME;
    _game->SetLocalClientId(INetClient::GetLocalClientId());
    INetClient::SetRemoteGameUdpEndpoint(sf::IpAddress(gameIp), gamePort);
}