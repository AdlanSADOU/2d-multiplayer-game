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
    sf::Packet inClientKeyPacket = event.GetParam<sf::Packet>(0);

    ClientID  clientId;
    sf::Int32 pressedKey  = -1;
    sf::Int32 releasedKey = -1;
    bool      isFiering   = false;

    if (clientId == _localClientId)
        return;

    inClientKeyPacket >> clientId
        >> pressedKey >> releasedKey
        >> isFiering;

    if (pressedKey == (nuts::Key::A)) {
        _players[clientId]->_directionalKeys[0] = true;
    }
    if (pressedKey == (nuts::Key::D)) {
        _players[clientId]->_directionalKeys[1] = true;
    }
    if (pressedKey == (nuts::Key::W)) {
        _players[clientId]->_directionalKeys[2] = true;
    }
    if (pressedKey == (nuts::Key::S)) {
        _players[clientId]->_directionalKeys[3] = true;
    }

    _players[clientId]->Move();

    if (releasedKey == (nuts::Key::A)) {
        _players[clientId]->_directionalKeys[0] = false;
    }
    if (releasedKey == (nuts::Key::D)) {
        _players[clientId]->_directionalKeys[1] = false;
    }
    if (releasedKey == (nuts::Key::W)) {
        _players[clientId]->_directionalKeys[2] = false;
    }
    if (releasedKey == (nuts::Key::S)) {
        _players[clientId]->_directionalKeys[3] = false;
    }

    _players[clientId]->SetFiering(isFiering);
}

bool RTypeGame::IsMonsterInList(int id)
{
    return (false);
}

void RTypeGame::OnMonsterUpdatePos(Event &event)
{
    sf::Packet packet = event.GetParam<sf::Packet>(0);

    int id;
    int type;
    float posX;
    float posY;


    while (!packet.endOfPacket()) {
        packet >> id >> type >> posX >> posY;

        if (_monsters.find(id) == std::end(_monsters)) {
            _monsters.insert({id, GMonster((GMonster::MInfos){id, (GMonster::Type)type, (nuts::Vector2f){posX, posY}}, _MTextures[(GMonster::Type)type], _MTexturesRect[(GMonster::Type)type], _MFrameCount[(GMonster::Type)type])});
        }
        auto &tComp = _monsters[id].GetComponent<TransformComponent>();
        tComp = {posX, posY};
    }
}