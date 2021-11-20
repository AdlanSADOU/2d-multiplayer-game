/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RTypeGameNet.cpp
*/

#include "RTypeGame.hpp"

void RTypeGame::OnInitialGameInfo(Event &event)
{
    sf::Packet packet = event.GetParam<sf::Packet>(0);

    std::vector<ClientID> clientIds;

    while (!packet.endOfPacket()) {
        ClientID tmpId;
        packet >> tmpId;

        clientIds.push_back(tmpId);
        _players.insert({ tmpId, new GPlayer(tmpId) });

        std::cout << "[Client]: Starting game with playerId:[" << tmpId << "]\n";
    }
    isReady = true;
};

// process key events from other clients in the game
void RTypeGame::OnRemotePlayerState(Event &event)
{
    sf::Packet &inClientStatePacket = event.GetParam<sf::Packet>(0);

    ClientID  clientId    = -1;

    if (clientId == _localClientId)
        return;

    inClientStatePacket
        >> clientId
        >> _players[clientId]->_directionalKeys[0]
        >> _players[clientId]->_directionalKeys[1]
        >> _players[clientId]->_directionalKeys[2]
        >> _players[clientId]->_directionalKeys[3]
        >> _players[clientId]->_isFiering;

    // std::cout << "OnRemotePlayerState() -> " << clientId
    //     << _players[clientId]->_directionalKeys[0]
    //     << _players[clientId]->_directionalKeys[1]
    //     << _players[clientId]->_directionalKeys[2]
    //     << _players[clientId]->_directionalKeys[3]
    //     << _players[clientId]->_isFiering << "\n";
}
