
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <Nuts/Networking.hpp>

#include <stdio.h>
#include <vector>
#include <array>
#include <unordered_map>

#include <Server.hpp>


int main()
{

	Server server;

	server.Init();
	server.Listen(55001);

	while (server.IsRunning())
	{
		server.Accept();
		server.Dispatch();
	}

	server.ShutDown();
	return 0;
}
