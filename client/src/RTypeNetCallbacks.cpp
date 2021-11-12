/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** RtypeNetworkCallbacks.cpp
*/

#include "RType.hpp"

void RType::OnNetReceivedId(Event &event)
{
    sf::Packet packet = event.GetParam<sf::Packet>(0);
    ClientID id;
    packet >> id;

    SetLocalClientId(id);

    std::cout << "OnNetReceivedId id:"
              << GetLocalClientId()
              << "\n";
}
