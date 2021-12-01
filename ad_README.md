# Remarks
git submodule update --force --init --remote



RType.cpp => GameThread.hpp => RTypeGameNet.cpp

- ditch Lobby

CLIENT_ID       : server sends
MATCHM_OK       : server responds
GAMEID          : server responds
GAMEID_OK       : client responds
INITIAL_GAME_INFO : server sends

CLIENT_UDP      : client sends
MATCHM_INIT     : client sends
MATCHM_PLAY     : client sends

[Quick Play] ==>
- [client] connect

- [server]  accept - respond with CLIENT_ID|clientId

- [client]  store id -
            UdpSend(sIp, sPort+1, CLIENT_UDP|ClienId|UdpPort)
            respond with MATCHM_INIT|clientId

- [server]  onMATCHM_INIT:
            Machmaking is running?:
                YES: Matchm.addClient(SClient)
                    Broadcast("new client joined")
                    Send(MATCHM_OK|ClienId)

                NO: create new Machmacking
                    Matchm.addClient(SClient)
                    Send(MATCHM_OK|ClienId)

- [client]  onMATCHM_OK:
            screen shows: "Waiting for players..."
            with blurred background
            players can click on [Play] or wait for others
                [Play] Send(MATCHM_PLAY|ClientId)

- [server]  onMATCHM_PLAY: inits new Game thread
            pushes all clients from Matchm to Game
            binds Game udpSock
            tcpBroadCast(GAMEID|gameId)

- [client]  onGAMEID:
            store gameId
            TcpSend(GAMEID_OK|gameId|clienId)

- [server] TcpSend(INITIAL_GAME_INFO|color|InitialGamePos)
           UdpBroadcast(UDP_INFO)

now clients can start sendind input commands in Udp

## Matchmaking

# Notes
VSCODE: possible conflicts for includes between c_cpp_configuration.json
and Cmake configuration provider in settings.json

x64 == x86_64 == x86_amd64 == Amd64


conan install .. --build=missing -s build_type=Debug
cmake .. -G "Visual Studio 16 2019" -A x64


cmake build static libraries:
https://cmake.org/cmake/help/latest/guide/tutorial/Selecting%20Static%20or%20Shared%20Libraries.html
https://code.austinmorlan.com/austin/ecs/src/branch/master/Source/Core/Event.hpp



# Server Issues

# TODO
Event loop must be run by the client
not the engine
cause engine is a shared lib, so static function isKeyPressed() executes on all clients...


# TODO Engine
sfml types must be typedefed by nuts or somehow encapsulated for consistency's sake

prediction
le plus proche de rtype
design
sounds

# Client/Server

When the game is first launched & loaded you are in the MainMenu

The game can ONLY be played in multiplayer

So when you launch the game, your `[Client] first tries to [CONNECT] to the server`.

The `[Server] then replies with your attributed [ID]` and you land on the lobby screen.

Once in the [Lobby_Screen] your [Client] tells the server that it is in the [Lobby_Screen]
The `server sends a list of any existing lobbys -> list[LobbyId]` or `-1 if no lobbys exist`.
Your `client then draws a button list of those lobbys` and `when clicked, a request to join the lobby is sent to the server`.

The server then associates your client ID with the lobby id and send back a [LOBBY_JOINED] response upon success followed by a list of all clients that already joined the lobby. For every client that joins the lobby, the server broadcast to all those clients an updated list with the newly joined client.

Once in a lobby clients have a [READY] button, when clicked, server receives a packet with the format [CLIENT_READY][lobbyId][clientId]

When the last client in the lobby clicks the [READY] button, the server receives a [START_GAME] packet, which inits a game session on the server side and broadcasts to all clients data related to the game session. the client can now start to load the necessary sprite assets to start drawing all entities received from the server.

###### not actually sure about what follows (turned out exactly as stated)
Each GameSession could be a thread, that thread has its own UDP socket that only clients belonging to that session can communicate with


---
## Thread workers example & mutex
https://en.cppreference.com/w/cpp/thread/mutex

    std::vector<std::thread> workers;

    for (int i = 0; i < 5; i++) {
        workers.push_back(std::thread([]()
        {
            std::cout << "thread function\n";
        }));
    }

    std::for_each(workers.begin(), workers.end(), [](std::thread &t)
    {
        t.join();
    });

### threading obeservations
trying to join workers ouside the class they were pushed
crashes


# Client/Server Protocol
https://www.netresec.com/index.ashx?page=RawCap

- sequence diagram

# UDP
- Delivery of any given datagram is not guaranteed. Any datagram may be lost at any time.
- Order of delivery is not guaranteed. Datagrams are not necessarily received in the same order in which they were sent.
- Uniqueness of delivery is not guaranteed. Any given datagram may be delivered more than once.