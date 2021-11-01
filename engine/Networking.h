/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** Networking.h
*/

#pragma once

#include <iostream>

using ClientID = std::uint8_t;
using Rpc = std::uint8_t;
namespace ERpc
{
    const Rpc CLIENT_CONNECT = 0;
    const Rpc CLIENT_DISCONNECT = 1;
    const Rpc LOBBY_CREATE = 2;
    const Rpc LOBBY_ID = 3;
}
