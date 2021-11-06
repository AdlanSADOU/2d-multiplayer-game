#include "SClientManager.hpp"

void SClientManager::RegisterClient(sf::TcpSocket* socket)
{
    if (socket == nullptr)
        return;

    SClient tmpClient;
    tmpClient.tcp = socket;
    tmpClient.connected = true;
    tmpClient.IsInLobby = false;
    tmpClient.uuid = _clientId;
    clients.insert({ _clientId, tmpClient });

    sf::Packet idPacket;
    idPacket << static_cast<sf::Uint8>(ERpc::CLIENT_CONNECT) << tmpClient.uuid;

    sf::Socket::Status status;
    if ((status = socket->send(idPacket)) != sf::Socket::Done)
        printf("[SERVER]:CLIENT_CONNECT::Error: Status:[%d]", status);

    printf("[SERVER]: Client connected as ID:[%d] from [%s:%d]\n\n",
        _clientId, socket->getRemoteAddress().toString().c_str(), tmpClient.tcp->getRemotePort());

    lobby.AddClient(&clients.at(_clientId));
    ++_clientId;
};

void SClientManager::AddClientUdpPort(sf::Uint16 udpPort, ClientID remoteId)
{
    printf("[SERVER]: added udpPort:[%d] to client[%d]\n", udpPort, remoteId);
    clients.find(remoteId)->second.updPort = udpPort;
    
}

bool SClientManager::DisconnectClient(ClientID remoteId)
{
    // assert(clients.find(remoteId) != clients.end() && "Removing non-existant client.");
    // if (clients.find(remoteId) != clients.end()) return false;

    for (auto& client : clients) {
        if (client.second.uuid == remoteId) {
            printf("[SERVER]: client disconnected ID:[%d] from [%s:%d] || sockPtr:[%p]\n",
                client.second.uuid, client.second.tcp->getRemoteAddress().toString().c_str(), client.second.tcp->getRemotePort(), client.second.tcp);
            client.second.tcp->disconnect();
            client.second.connected = false;
            if (client.second.tcp)
                delete client.second.tcp;
            clients.erase(remoteId);
            return true;
        }
    }
    return false;
}

void SClientManager::PrintConnectedClients()
{
    printf("[SERVER]: Connected clients:\n");
    for (auto const& client : clients) {

        printf("------ ID:[%d] from [%s:%d] | sockPtr:[%p]\n",
            client.second.uuid, client.second.tcp->getRemoteAddress().toString().c_str(), client.second.tcp->getRemotePort(), client.second.tcp);
    }
}

