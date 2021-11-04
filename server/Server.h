#include "Nuts/Networking.h"

#include <vector>

#include "Sclient.h"

class Server
{
private:

std::vector<Sclient> clients;
std::vector<sf::TcpSocket *> clientSockets;

public:
    Server() {};
    ~Server() {};
	Sclient &GetClientById() {

	};
};
