/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RTypeMenu
*/

#pragma once

#include <Nuts/Engine.hpp>
#include <Nuts/UI/Button.hpp>
#include <Nuts/UI/Widget.hpp>
#include <Nuts/UI/Text.hpp>

#include "UIEvents.hpp"

class RTypeMenu
{
    struct WidgetMenu
    {
        nuts::UI::Widget logo;
        nuts::UI::Widget panel;
        nuts::UI::Button btnLobby;
        nuts::UI::Button btnQuit;
    };

    private:
        nuts::Font _font;

    public:
        std::shared_ptr<nuts::Engine> _engine;
        WidgetMenu                    _widgetMenu;

        RTypeMenu();
        ~RTypeMenu();

        void Init(std::shared_ptr<nuts::Engine> engine);


};
