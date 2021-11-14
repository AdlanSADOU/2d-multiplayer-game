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

void RTypeMenu::Init(std::shared_ptr<nuts::Engine> engine)
{
    _engine                = engine;
    nuts::Vector2u winSize = _engine->GetWindowSize();

    _font.LoadFromFile("./resources/fonts/arial.ttf");

    _widgetMenu.btnLobby.GetText().SetFont(_font);
    _widgetMenu.btnLobby.GetText().SetString("Hellooooooooo");
    _widgetMenu.btnLobby.GetText().SetCharacterSize(40);
    _widgetMenu.btnLobby.GetText().SetFillColor((nuts::Color){255, 255, 255, 255});

    _widgetMenu.logo     = nuts::UI::Widget("Logo");
    _widgetMenu.panel    = nuts::UI::Widget("Panel");
    _widgetMenu.btnLobby = nuts::UI::Button("Lobby");

    _widgetMenu.logo.SetImageFromFile("./resources/r_type_logo.png");
    _widgetMenu.panel.SetImageFromFile("./resources/ui/MainPanel02.png");
    _widgetMenu.btnLobby.SetImageFromFile("./resources/ui/Button01.png");

    _widgetMenu.panel.SetParent(_widgetMenu.logo);
    _widgetMenu.btnLobby.SetParent(_widgetMenu.panel);
    _widgetMenu.btnLobby.SetEventType(Events::Btn::BTN_LOBBY_SCREEN);

    float lgWidth    = _widgetMenu.logo.GetSprite().GetSprite().getLocalBounds().width;
    float lgHeight   = _widgetMenu.logo.GetSprite().GetSprite().getLocalBounds().height;
    float panelWidth = _widgetMenu.panel.GetSprite().GetSprite().getLocalBounds().width;
    float lbBtnWidth = _widgetMenu.btnLobby.GetSprite().GetSprite().getLocalBounds().width;

    _widgetMenu.logo.SetPosition({ winSize.x / 2.f - lgWidth / 2.f, 0 });
    _widgetMenu.panel.SetPosition({ lgWidth / 2.f - panelWidth / 2.f, lgHeight - 20 });
    _widgetMenu.btnLobby.SetPosition({ lbBtnWidth / 2.f, 20 });
    _widgetMenu.btnLobby.GetText().SetPosition({0, 0});
}
