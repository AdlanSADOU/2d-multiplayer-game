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

    nuts::Color score_colors[4] = {
        nuts::Color(128, 0, 128, 100),
        nuts::Color(0, 255, 0, 100),
        nuts::Color(255, 0, 0, 100),
        nuts::Color(0, 0, 255, 100),
    };

    while (!packet.endOfPacket())
    {
        ClientID tmp_client_id;
        packet >> tmp_client_id;

        clientIds.push_back(tmp_client_id);
        _players.insert({ tmp_client_id, new GPlayer(tmp_client_id) });

        nuts::Text  tmp_text = {};
        std::string tmp_str  = "P.";
        tmp_str.append(std::to_string(tmp_client_id));

        tmp_text.SetString(tmp_str);
        tmp_text.SetOutlineThickness(.8f);
        tmp_text.SetOulineColor(score_colors[tmp_client_id % MAX_CLIENTS]);
        tmp_text.SetFont(_font);
        tmp_text.SetCharacterSize(12);

        thread_local float text_pos = 100;
        tmp_text.SetPosition({ text_pos, (float)_engine->GetWindowSize().y / 6 * 5 });
        _player_scores.insert({ tmp_client_id, tmp_text });
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