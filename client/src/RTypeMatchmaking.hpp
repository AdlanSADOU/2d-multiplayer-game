/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RTypeMatchmaking
*/

#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Nuts/Engine.hpp"

#include "Nuts/UI/Text.hpp"

class RTypeMMPlayer
{
    public:
        enum MPlayerState
        {
            NREADY,
            READY
        };

        RTypeMMPlayer() {}

        RTypeMMPlayer(const std::string &name) {
            _name = name;
        }

        ~RTypeMMPlayer() {}

        void SetName(const std::string &name)
        {
            _name = name;
        }

        const std::string GetName()
        {
            return (_name);
        }

        void SetState(MPlayerState state)
        {
            _state = state;
        }

        const MPlayerState GetState()
        {
            return (_state);
        }

        void SetID(int id)
        {
            _id = id;
        }

        const int &GetID()
        {
            return (_id);
        }

        private:
            std::string _name = "";
            MPlayerState _state = MPlayerState::NREADY;
            int _id;
};

class RTypeMatchmaking
{

    private:
        std::shared_ptr<nuts::Engine> _engine;

        std::vector<RTypeMMPlayer> _players;

        nuts::Font _font;
        nuts::Text _tReady;
        nuts::Text _tNReady;
        std::vector<nuts::Text> _tPlayers;


    public:
        RTypeMatchmaking()
        {

        }

        ~RTypeMatchmaking()
        {

        }

        std::vector<RTypeMMPlayer> &GetPlayers()
        {
            return (this->_players);
        }

        void Draw()
        {
            int x = 0;
            for (auto &player : _tPlayers) {
                player.Draw(_engine->window);
                nuts::FloatRect pPos = player.GetGlobalBounds();
                nuts::Text tmp;
                if (_players[x].GetState() == RTypeMMPlayer::MPlayerState::READY) {
                     tmp = _tReady;
                    tmp.SetPosition({pPos.left + pPos.width + 50, pPos.top});
                }
                else {
                    tmp = _tNReady;
                    tmp.SetPosition({pPos.left + pPos.width + 50, pPos.top});
                }
                tmp.Draw(_engine->window);
            }
        }

        void Init(std::shared_ptr<nuts::Engine> engine)
        {
            _engine = engine;
            _font.LoadFromFile("./resources/fonts/arcade.ttf");

            _players.emplace_back(RTypeMMPlayer("Player 1"));
            _players.emplace_back(RTypeMMPlayer("Player 2"));
            _players.emplace_back(RTypeMMPlayer("Player 3"));
            _players.emplace_back(RTypeMMPlayer("Player 4"));

            _tPlayers.emplace_back(nuts::Text(_players[0].GetName(), 12, _font));
            _tPlayers.emplace_back(nuts::Text(_players[1].GetName(), 12, _font));
            _tPlayers.emplace_back(nuts::Text(_players[2].GetName(), 12, _font));
            _tPlayers.emplace_back(nuts::Text(_players[3].GetName(), 12, _font));

            _tNReady = nuts::Text("Not ready", 12, _font);
            _tNReady.SetFillColor({255, 0, 0, 255});

            _tReady = nuts::Text("Ready", 12, _font);
            _tReady.SetFillColor({0, 255, 0, 255});

            float y = 0;
            for (auto &player : _tPlayers) {
                player.SetPosition({50, y += 50});
            }
        }
};
