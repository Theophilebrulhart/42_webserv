/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:57:16 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/29 21:02:52 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestServer.hpp"

SERVER::TestServer::TestServer() : AServer(AF_INET, SOCK_STREAM, 0, 80,
INADDR_ANY, 35)
{
	launch();
    return ;
}

SERVER::TestServer::~TestServer(void)
{
    return ;
}

void    SERVER::TestServer::_accepter(void)
{
    struct  sockaddr_in address = getServerSocket()->getAddress();
    int     addrlen = sizeof(address);
	std::vector<char>	buf(1000);

    _newSocket = accept(getServerSocket()->getSocketFd(), (struct sockaddr *)&address,
                        (socklen_t *)&addrlen);
	if (_newSocket < 0)
	{
		std::cerr << "Failed to accept socket\n";
		exit (EXIT_FAILURE);
	}
	bzero(buf.data(), buf.size());
	if (recv(_newSocket, buf.data(), buf.size(), 0) < 0)
	{
		std::cerr << "Failed recv\n";
		exit (EXIT_FAILURE);
	}
	std::string str(buf.begin(), buf.end());
	_buffer = str;
	//std::cout << _buffer << std::endl;
	std::cout << "\naccepter end\n\n";
	return ;
}

void	SERVER::TestServer::_handler(int clientSocket)
{
	//std::cout << "\ntests\n";
	requestParsing(_buffer, _requestInfo);
	
	if (_requestInfo.at("METHOD") == "POST")
	{
		try
		{
			_requestInfo.at("CONTENT-TYPE");
			formParsing (_buffer, _requestInfo, clientSocket, _responsContent);
		}
		catch(const std::out_of_range& oor)
		{
			std::cout << "\nNo multipart/form-data\n";
		}
	}
	if (_requestInfo.at("METHOD") == "DELETE")
	{
		try
		{
			_requestInfo.at("CONTENT-TYPE");
			deleteFile(_requestInfo, _responsContent);
		}
		catch(const std::out_of_range& oor)
		{
			std::cout << "\nNo multipart/form-data\n";
		}
	}
	if (_requestInfo.at("METHOD") == "GET")
		openFile(_requestInfo, _responsContent);
	return ;
}

void	SERVER::TestServer::_responder(int clientSocket)
{
	RESPONS::CreateRespons	createRespons(_responsContent);
	std::string respons = createRespons.getRespons();
	std::cout << "\n\e[0;93m*****RESPONDER****\n" << respons;
	send(clientSocket, respons.c_str(), respons.size(), 0);
	//std::cout << "send done\n";
	close(_newSocket);

	std::map<std::string, std::string>::const_iterator it;
    for (it = _responsContent.begin(); it != _responsContent.end(); )
	{
		_responsContent.erase(it++);
	}
	return ;
}

void	SERVER::TestServer::launch(void)
{
	std::cout << "\e[0;31m****STARTING*****\e[0m\n";
	fd_set readfds;
	int initialSocket = getServerSocket()->getSocketFd();
    FD_ZERO(&readfds);
    FD_SET(initialSocket, &readfds);
    int maxfd =(initialSocket);

    // Liste des sockets des clients
    std::vector<int> clientSockets;

    while (true) {
        fd_set tempfds = readfds;  // Copie de l'ensemble des descripteurs de fichiers

        // Utilisation de select() pour attendre des événements sur les sockets
		std::cout << "\n\e[0;32m===== WAITING =====\e[0m\n";
        int activity = select(maxfd + 1, &tempfds, nullptr, nullptr, nullptr);
        if (activity == -1) {
            std::cerr << "Erreur lors de l'appel à select()." << std::endl;
            close(initialSocket);
            return ;
        }

        // Nouvelle connexion entrante
        if (FD_ISSET(initialSocket, &tempfds)) {
            // Accepter la nouvelle connexion
            int clientSocket = accept(initialSocket, nullptr, nullptr);
            if (clientSocket == -1) {
                std::cerr << "Erreur lors de l'acceptation de la connexion." << std::endl;
                close(initialSocket);
                return ;
            }

            // Ajouter le socket client à la liste
            clientSockets.push_back(clientSocket);
            std::cout << "Nouvelle connexion entrante." << std::endl;

            // Mettre à jour le descripteur de fichier maximal
            if (clientSocket > maxfd)
                maxfd = clientSocket;

            // Ajouter le socket client à l'ensemble des descripteurs de fichiers
            FD_SET(clientSocket, &readfds);
        }

        // Vérifier les sockets des clients existants pour les données entrantes
        for (size_t i = 0; i < clientSockets.size(); ++i) {
            int clientSocket = clientSockets[i];

            if (FD_ISSET(clientSocket, &tempfds)) {
                char buffer[1000];
                memset(buffer, 0, sizeof(buffer));

                // Lire les données reçues
                ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
                if (bytesRead == -1) {
                    std::cerr << "Erreur lors de la réception des données." << std::endl;
                    close(initialSocket);
                    return ;
                }

                if (bytesRead == 0) {
                    // Le client a fermé la connexion
                    std::cout << "Connexion fermée." << std::endl;
                    close(clientSocket);
                    FD_CLR(clientSocket, &readfds);
                    clientSockets.erase(clientSockets.begin() + i);
                    --i;
                } else {
                    // Faire quelque chose avec les données reçues
					_buffer = buffer;
					_handler(clientSocket);
					_responder(clientSocket);
                }
            }
        }
		std::cout << "\e[0;36m\n===== DONE =====\e[0m\n";
    }

    // Fermer le socket du serveur
    close(initialSocket);

    return ;
}