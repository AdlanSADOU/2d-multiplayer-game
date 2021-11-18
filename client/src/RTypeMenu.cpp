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

    _font.LoadFromFile("./resources/fonts/arcade.ttf");

    _widgetMenu.logo     = nuts::UI::Widget("Logo");
    _widgetMenu.panel    = nuts::UI::Widget("Panel");
    _widgetMenu.btnLobby = nuts::UI::Button("Lobby");
    _widgetMenu.btnQuit  = nuts::UI::Button("Quit");

    _widgetMenu.btnQuit.GetText().SetFont(_font);
    _widgetMenu.btnQuit.GetText().SetString("Quit");
    _widgetMenu.btnQuit.GetText().SetCharacterSize(11);
    _widgetMenu.btnQuit.GetText().SetFillColor({255, 255, 255, 255});

    _widgetMenu.btnLobby.GetText().SetFont(_font);
    _widgetMenu.btnLobby.GetText().SetString("Quickmatch");
    _widgetMenu.btnLobby.GetText().SetCharacterSize(11);
    _widgetMenu.btnLobby.GetText().SetFillColor({255, 255, 255, 255});

    _widgetMenu.logo.SetImageFromFile("./resources/r_type_logo.png");
    _widgetMenu.panel.SetImageFromFile("./resources/ui/MainPanel02.png");
    _widgetMenu.btnLobby.SetImageFromFile("./resources/ui/Button01.png");
    _widgetMenu.btnQuit.SetImageFromFile("./resources/ui/Button01.png");

    _widgetMenu.panel.SetParent(_widgetMenu.logo);
    _widgetMenu.btnLobby.SetParent(_widgetMenu.panel);
    _widgetMenu.btnQuit.SetParent(_widgetMenu.panel);
    _widgetMenu.btnLobby.SetEventType(Events::Btn::BTN_LOBBY_SCREEN);
    _widgetMenu.btnQuit.SetEventType(Events::Btn::BTN_QUIT);

    float lgWidth     = _widgetMenu.logo.GetSprite().GetSprite().getLocalBounds().width;
    float lgHeight    = _widgetMenu.logo.GetSprite().GetSprite().getLocalBounds().height;
    float panelWidth  = _widgetMenu.panel.GetSprite().GetSprite().getLocalBounds().width;
    float panelHeight = _widgetMenu.panel.GetSprite().GetSprite().getLocalBounds().height;
    float lbBtnWidth  = _widgetMenu.btnLobby.GetSprite().GetSprite().getLocalBounds().width;
    float lbBtnHeight = _widgetMenu.btnLobby.GetSprite().GetSprite().getLocalBounds().height;
    float qtBtnWidth  = _widgetMenu.btnQuit.GetSprite().GetSprite().getLocalBounds().width;
    float qtBtnHeight = _widgetMenu.btnQuit.GetSprite().GetSprite().getLocalBounds().height;

    nuts::FloatRect textLbBtn = _widgetMenu.btnLobby.GetText().GetLocalBounds();
    nuts::FloatRect textQtBtn = _widgetMenu.btnQuit.GetText().GetLocalBounds();

    _widgetMenu.logo.SetPosition({ winSize.x / 2.f - lgWidth / 2.f, 0 });
    _widgetMenu.panel.SetPosition({ lgWidth / 2.f - panelWidth / 2.f, lgHeight - 20 });
    _widgetMenu.btnLobby.SetPosition({ lbBtnWidth / 2.f, 20 });
    _widgetMenu.btnQuit.SetPosition({ qtBtnWidth / 2.f, panelHeight - 60 });

    nuts::Vector2f lbBtnPos = _widgetMenu.btnLobby.GetPosition();
    nuts::Vector2f qtBtnPos = _widgetMenu.btnQuit.GetPosition();

    _widgetMenu.btnLobby.GetText().SetPosition({ lbBtnPos.x + lbBtnWidth / 2 - textLbBtn.width / 2, lbBtnPos.y + lbBtnHeight / 2 - textLbBtn.height / 2 });
    _widgetMenu.btnQuit.GetText().SetPosition({ qtBtnPos.x + qtBtnWidth / 2 - textQtBtn.width / 2, qtBtnPos.y + qtBtnHeight / 2 - textQtBtn.height / 2 });
}