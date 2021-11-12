/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RTypeMenu
*/

#pragma once

#include <Nuts/UI/Widget.hpp>

class RTypeMenu
{
    struct WidgetMenu
    {
        nuts::UI::Widget _background;
        nuts::UI::Widget _panel;
    };

public:
    WidgetMenu _widgetMenu;

    RTypeMenu();
    ~RTypeMenu();

    void Init();

protected:
private:
};
