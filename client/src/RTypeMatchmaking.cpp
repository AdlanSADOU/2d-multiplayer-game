/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RTypeMatchmaking
*/

#include "RTypeMatchmaking.hpp"

RTypeMatchmaking::RTypeMatchmaking()
{
    auto p1 = RTypeMMPlayer("Player 1");
    auto p2 = RTypeMMPlayer("Player 2");
    auto p3 = RTypeMMPlayer("Player 3");
    auto p4 = RTypeMMPlayer("Player 4");

    _players.emplace_back(p1);
    _players.emplace_back(p2);
    _players.emplace_back(p3);
    _players.emplace_back(p4);
}

RTypeMatchmaking::~RTypeMatchmaking()
{

}

std::vector<RTypeMMPlayer> &RTypeMatchmaking::GetPlayers()
{
    return (this->_players);
}



void RTypeMatchmaking::Init()
{
    _font.LoadFromFile("./resources/fonts/arcade.ttf");


}