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
        ClientID tmp_client_id;
        packet >> tmp_client_id;

        clientIds.push_back(tmp_client_id);
        _players.insert({ tmp_client_id, new GPlayer(tmp_client_id) });

        nuts::Text tmp_text = {};
        std::string tmp_str = "P.";
        tmp_str.append(std::to_string(tmp_client_id));

        tmp_text.SetString(tmp_str);

        tmp_text.SetFont(_font);
        tmp_text.SetCharacterSize(12);

        thread_local float text_pos = 100;
        tmp_text.SetPosition({ text_pos, (float)_engine->GetWindowSize().y / 6 * 5 });
        _player_scores.insert({tmp_client_id, tmp_text});
        text_pos += 100;

        std::cout << "[Client]: Starting game with playerId:[" << tmp_client_id << "]\n";
    }
    isReady = true;
};

// process key events from other clients in the game
void RTypeGame::OnRemotePlayerState(Event &event)
{
    sf::Packet inClientStatePacket = event.GetParam<sf::Packet>(0);

    ClientID client_id = -1;
    float    x = 0, y = 0;

    if (client_id == _localClientId)
        return;

    thread_local int32_t last_score;

    if (inClientStatePacket
        >> client_id
        >> _players[client_id]->_directionalKeys[0]
        >> _players[client_id]->_directionalKeys[1]
        >> _players[client_id]->_directionalKeys[2]
        >> _players[client_id]->_directionalKeys[3]
        >> x
        >> y
        >> _players[client_id]->_isFiering
        >> _players[client_id]->_score

    ) {
        _players[client_id]->SetPosition({ x, y });

        if (last_score != _players[client_id]->_score)
            COUT("player " << client_id << " Score: " << _players[client_id]->_score << "\n");

        // std::cout << client_id << ": "
        //           << _players[client_id]->_directionalKeys[0]
        //           << _players[client_id]->_directionalKeys[1]
        //           << _players[client_id]->_directionalKeys[2]
        //           << _players[client_id]->_directionalKeys[3]
        //           << _players[client_id]->_isFiering
        //           << "\n";
        last_score = _players[client_id]->_score;
    }
}

bool RTypeGame::IsMonsterInList(int id)
{
    return (false);
}

void RTypeGame::OnMonsterUpdatePos(Event &event)
{
    sf::Packet packet = event.GetParam<sf::Packet>(0);

    // pushing received packets into queue to process them later
    // with thread safety. see RTypeGame::ProcessMonsterPackets()
    _monster_packets_queue.push(packet);
}