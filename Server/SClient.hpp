#include <Nuts/Networking.hpp>

class SClient
{
    public:
        sf::TcpSocket *socket;
        ClientID uuid;
        bool registered;
        bool IsInLobby;
        std::uint8_t lobbyID;
};
