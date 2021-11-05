/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Networking.h
*/

#pragma once

#include <SFML/Network.hpp>
#include <iostream>

using ClientID = sf::Uint8;
using Rpc = sf::Uint8;

enum ERpc {
     CLIENT_CONNECT = 1,
     CLIENT_DISCONNECT,
     CLIENTS_PRINT,
     LOBBY_CREATE,
     LOBBY_ID,
};

#define RPC(x)(static_cast<sf::Uint8>(x))