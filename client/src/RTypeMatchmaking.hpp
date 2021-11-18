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
    struct WidgetMenu
    {
        nuts::UI::Widget panel;
        nuts::UI::Button startBtn;
    };

    private:
        std::shared_ptr<nuts::Engine> _engine;

        std::vector<RTypeMMPlayer> _players;

        nuts::Font _font;
        nuts::Text _tReady;
        nuts::Text _tNReady;
        std::vector<nuts::Text> _tPlayers;

        WidgetMenu _menu;

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
            _menu.panel.TEST_DRAW(_engine->window);
            _menu.startBtn.TEST_DRAW(_engine->window);
            _menu.startBtn.GetText().Draw(_engine->window);
            for (auto &player : _tPlayers) {
                nuts::FloatRect pPos = player.GetGlobalBounds();
                nuts::Text tmp;
                if (_players[x].GetState() == RTypeMMPlayer::MPlayerState::READY) {
                     tmp = _tReady;
                }
                else {
                    tmp = _tNReady;
                }
                player.Draw(_engine->window);
                tmp.SetPosition({pPos.left + pPos.width + 15, pPos.top});
                tmp.SetCharacterSize(8);
                tmp.Draw(_engine->window);
            }
        }

        void Init(std::shared_ptr<nuts::Engine> engine)
        {
            _engine = engine;
            _font.LoadFromFile("./resources/fonts/arcade.ttf");
            nuts::Vector2u winSize = _engine->GetWindowSize();

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

            _menu.panel = nuts::UI::Widget("Panel");
            _menu.panel.SetImageFromFile("./resources/ui/MainPanel02.png");
            _menu.startBtn = nuts::UI::Button("Start");
            _menu.startBtn.SetImageFromFile("./resources/ui/Button01.png");

            _menu.startBtn.GetText().SetFont(_font);
            _menu.startBtn.GetText().SetString("Play");
            _menu.startBtn.GetText().SetCharacterSize(11);
            _menu.startBtn.GetText().SetFillColor({255, 255, 255, 255});

            _menu.startBtn.SetParent(_menu.panel);
            _menu.startBtn.SetEventType(::Events::Btn::BTN_START);

            float panelWidth = _menu.panel.GetSprite().GetSprite().getLocalBounds().width;
            float panelHeight = _menu.panel.GetSprite().GetSprite().getLocalBounds().height;
            float btnWidth = _menu.startBtn.GetSprite().GetSprite().getLocalBounds().width;
            float btnHeight = _menu.startBtn.GetSprite().GetSprite().getLocalBounds().height;

            _menu.panel.SetPosition({ winSize.x / 2.f - panelWidth / 2.f, winSize.y / 2.f - panelHeight / 2.f});
            nuts::Vector2f panelPos = _menu.panel.GetPosition();

            _menu.startBtn.SetPosition({panelWidth / 2 - btnWidth / 2, panelHeight + 10});

            nuts::Vector2f stBtnPos = _menu.startBtn.GetPosition();
            nuts::FloatRect textStBtn = _menu.startBtn.GetText().GetLocalBounds();

            _menu.startBtn.GetText().SetPosition({stBtnPos.x + btnWidth / 2 - textStBtn.width / 2, stBtnPos.y + btnHeight / 2 - textStBtn.height / 2});

            float y = 50;
            for (auto &player : _tPlayers) {
                auto pLBounds = player.GetLocalBounds();
                player.SetPosition({panelPos.x + pLBounds.width / 2, panelPos.y + y});
                y += 90;
            }
        }
};
