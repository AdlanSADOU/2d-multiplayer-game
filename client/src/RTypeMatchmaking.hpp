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

#include "Text.hpp"

class RTypeMMPlayer
{
    typedef enum MPlayerState
    {
        NREADY,
        READY
    };

    private:
        std::string _name = "";
        MPlayerState _state = MPlayerState::NREADY;

    public:
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

};

class RTypeMatchmaking
{
    private:
        std::vector<RTypeMMPlayer> _players;
        std::shared_ptr<nuts::Engine> _engine;

        std::vector<nuts::Text> _tPlayers;

        nuts::Font _font;

    public:
        RTypeMatchmaking();
        ~RTypeMatchmaking();

        void Draw();
        void Init(std::shared_ptr<nuts::Engine> engine);

        std::vector<RTypeMMPlayer> &GetPlayers();

};
