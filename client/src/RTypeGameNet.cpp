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
    sf::Packet inClientStatePacket = event.GetParam<sf::Packet>(0);

    ClientID clientId = -1;
    float    x = 0, y = 0;

    if (clientId == _localClientId)
        return;

    if (inClientStatePacket
        >> clientId
        >> _players[clientId]->_directionalKeys[0]
        >> _players[clientId]->_directionalKeys[1]
        >> _players[clientId]->_directionalKeys[2]
        >> _players[clientId]->_directionalKeys[3]
        >> x
        >> y
        >> _players[clientId]->_isFiering) {
        _players[clientId]->SetPosition({ x, y });
        // std::cout << clientId << ": "
        //           << _players[clientId]->_directionalKeys[0]
        //           << _players[clientId]->_directionalKeys[1]
        //           << _players[clientId]->_directionalKeys[2]
        //           << _players[clientId]->_directionalKeys[3]
        //           << _players[clientId]->_isFiering
        //           << "\n";
    }
}

bool RTypeGame::IsMonsterInList(int id)
{
    return (false);
}

void RTypeGame::OnMonsterUpdatePos(Event &event)
{
    sf::Packet packet = event.GetParam<sf::Packet>(0);

    while (!packet.endOfPacket()) {
        int   id = -1;
        int   type;
        float posX;
        float posY;
        bool  destroyed = false;

        packet >> id >> type >> posX >> posY >> destroyed;

        if (id < 0) {
            COUT("Error: monster id was less than 0 : " << id << "\n");
            return;
        }

        if (!destroyed && _monsters.find(id) == std::end(_monsters)) {
            GMonster::MInfos minfos      = { id, (GMonster::Type)type, { posX, posY } };
            nuts::Texture   &texture     = _MTextures[(GMonster::Type)type];
            nuts::IntRect    rect        = _MTexturesRect[(GMonster::Type)type];
            int              frame_count = _MFrameCount[(GMonster::Type)type];

            // note(ad): monsters are now allocated to avoid double entity destruction
            GMonster *tmp = new GMonster(minfos, texture, rect, frame_count);
            _monsters.insert({ id, std::move(tmp) });
        }

        if (!destroyed && _monsters[id]) {
            auto &tComp                        = _monsters[id]->GetComponent<TransformComponent>();
            tComp                              = { posX, posY };
            _monsters[id]->_infos.is_destroyed = destroyed;
        }

        if (destroyed && (_monsters.find(id) != std::end(_monsters))) {
            scene.DestroyEntity(_monsters[id]->GetEntity());
            delete _monsters[id];
            _monsters[id] = nullptr;
            _monsters.erase(id);

            COUT("[UDP-REC]: depop monster with id: " << id << "\n");
            continue;
        }
    }
}