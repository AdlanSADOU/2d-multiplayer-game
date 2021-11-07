/*
** EPITECH PROJECT, 2021
** B-CPP-501-NCE-5-1-rtype-adlan.sadou
** File description:
** ServerMain.cpp
*/

#include <Server.hpp>


int main()
{
	Server server;

	server.Init();
	server.Listen(55001);

	while (server.IsRunning())
	{
		server.Accept();
		server.Receive();
	}

	server.ShutDown();
	return 0;
}
