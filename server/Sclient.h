#include <Nuts/Networking.h>

class Sclient
{
public:
    sf::TcpSocket *socket;
    ClientID uuid;
    bool registered;
    bool IsInLobby;
    std::uint8_t lobbyID;
};