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
    _isRunning = true;
};

// process key events from other clients in the game
void RTypeGame::OnRemoteKeyEvent(Event &event)
{
    sf::Packet &inClientKeyPacket = event.GetParam<sf::Packet>(0);

    ClientID  clientId;
    sf::Int32 pressedKey  = -1;
    sf::Int32 releasedKey = -1;

    inClientKeyPacket >> clientId >> pressedKey >> releasedKey;

    if (clientId == _localClientId)
        return;

    if (pressedKey == (nuts::Key::A)) {
        _players[clientId]->_pressedKeys[0] = true;
    }
    if (pressedKey == (nuts::Key::D)) {
        _players[clientId]->_pressedKeys[1] = true;
    }
    if (pressedKey == (nuts::Key::W)) {
        _players[clientId]->_pressedKeys[2] = true;
    }
    if (pressedKey == (nuts::Key::S)) {
        _players[clientId]->_pressedKeys[3] = true;
    }

    _players[clientId]->Move();

    if (releasedKey == (nuts::Key::A)) {
        _players[clientId]->_pressedKeys[0] = false;
    }
    if (releasedKey == (nuts::Key::D)) {
        _players[clientId]->_pressedKeys[1] = false;
    }
    if (releasedKey == (nuts::Key::W)) {
        _players[clientId]->_pressedKeys[2] = false;
    }
    if (releasedKey == (nuts::Key::S)) {
        _players[clientId]->_pressedKeys[3] = false;
    }
}