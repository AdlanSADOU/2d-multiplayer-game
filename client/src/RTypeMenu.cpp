/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RTypeMenu
*/

#include "RTypeMenu.hpp"

RTypeMenu::RTypeMenu()
{
}

RTypeMenu::~RTypeMenu()
{
}

void RTypeMenu::Init()
{
    _widgetMenu._background = nuts::UI::Widget("Background");
    _widgetMenu._background.SetImageFromFile("./resources/r_type_logo.png");
    _widgetMenu._background.SetPosition({ 0, 0 });

    _widgetMenu._panel = nuts::UI::Widget("Panel");
    _widgetMenu._panel.SetImageFromFile("./resources/me.jpg");
    _widgetMenu._panel.SetParent(_widgetMenu._background);
    _widgetMenu._panel.SetPosition({ 1, 0 });

    _widgetMenu._background.SetScale({.5f, .5f});
    _widgetMenu._panel.SetScale({ 1, 1 });
}
