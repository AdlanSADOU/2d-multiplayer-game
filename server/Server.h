#include <Networking.h>
#include <vector>

class Server
{
private:
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

public:
    Server() {};
    ~Server() {};
	GetClientById() {

	};
};
