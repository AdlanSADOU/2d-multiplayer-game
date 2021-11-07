# Remarks

- working conan profile:
```
[settings]
os=Windows
os_build=Windows
arch=x86_64
arch_build=x86_64
compiler=Visual Studio
compiler.version=16
build_type=Debug #or Release
[options]
[build_requires]
[env]
```

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
server accepts same incoming connection multiple times
  [really an issue? we can just not register it]

# TODO sever
## class Server
- Init()
- IsRunning()
- Listen()
- Accept()
---
## class Dispatcher
    dispacher takes in received packet and which socket type they came from (TCP or UDP)
    It then extracts the MsgType type and 'routes' to the approriate calls though an array of function pointers
    the Dispatcher has an array of function pointers indexed by MsgType type
    the Dispatcher holds unique references to ClientManager &
    LobbyManager

    - shared_ptr<ClientManager>
    - shared_ptr<LobbyManager>
    - std::array<(void)(*func)> RemoteProcedureCalls
    - Route()
---

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



###### not actually sure about what follows
Each GameSession could be a thread, that thread has its own UDP socket that only clients belonging to that session can communicate with


---
## Thread workers example
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

---
IServer common interface
- Clients

- TcpListener

- TcpSocket
- UdpSocket

- Listen()
- virtual Accept()

- sendMessage()
- receiveMessage()

IClient common interface
- clientId

- TcpSocket
- UdpSocket

- ConnectToServer()

- MessageType<T>

- MessageQueue<T>

- WriteMessageHeader()
- WriteMessageBody()

- ReadMessageHeader()
- ReadMessageBody()

- sendMessage(Connection, Packet)
- receiveMessage()