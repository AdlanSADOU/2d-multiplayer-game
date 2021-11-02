
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <NutsEngine.h>
#include <Networking.h>

#include <stdio.h>
#include <vector>
#include <array>


struct Client
{
	sf::TcpSocket *socket;
	ClientID uuid;
	bool registered;
	bool IsInLobby;
	std::uint8_t lobbyID;
};

std::vector<Client> clients;
std::vector<sf::TcpSocket *> clientSockets;

int main()
{
	sf::TcpListener listener;
	listener.setBlocking(false);
	listener.listen(55001);

	ClientID clientID = 0;

	printf("running server...\n");

	sf::TcpSocket tmpTcpClient;
	while (1)
	{
		if (listener.accept(tmpTcpClient) == sf::Socket::Done)
		{
			sf::TcpSocket *tcpSockPtr = new sf::TcpSocket();
			tcpSockPtr = &tmpTcpClient;

			printf("incomming connection\n");
			tcpSockPtr->setBlocking(false);
			clientSockets.push_back(tcpSockPtr);
		}
		else
		{
			for (auto &clientSocket : clientSockets)
			{
				sf::Packet remotePacket;
				Rpc rpcType = -1;

				sf::Socket::Status status = clientSocket->receive(remotePacket);
				if (status == sf::Socket::Done)
				{
					remotePacket >> rpcType;
					switch (rpcType)
					{
					case ERpc::CLIENT_CONNECT:
					{
						printf("new connection request from IP:[%s] | PORT:[%d]\n", clientSocket->getRemoteAddress().toString().c_str(), clientSocket->getRemotePort());
						Client tmpClient;
						tmpClient.socket = clientSocket;
						tmpClient.registered = true;
						tmpClient.IsInLobby = false;
						tmpClient.uuid = clientID;
						clients.push_back(tmpClient);
						printf("client registered as ID:[%d] from | IP:[%s] | PORT:[%d]\n", clientID, clientSocket->getRemoteAddress().toString().c_str(), clientSocket->getRemotePort());
						++clientID;

						sf::Packet idPacket;
						idPacket << ERpc::CLIENT_CONNECT << tmpClient.uuid;
						clientSocket->send(idPacket);
						break;
					}
					case ERpc::CLIENT_DISCONNECT:
					{
						ClientID remoteId;
						remotePacket >> remoteId;
						printf("client [%d] disconnected\n", remoteId);
						// clients should be unordered_map so we can call .find(id)
						break;
					}
					default:
						break;
					}
				}
			}
		}
	}

	return 0;
}
