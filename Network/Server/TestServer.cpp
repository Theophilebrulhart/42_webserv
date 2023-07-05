/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:57:16 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/05 16:42:21 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestServer.hpp"
#include "../Method/Utils.hpp"

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

int	SERVER::TestServer::_handler(int clientSocket)
{
	//std::cout << "\ntests\n";
    int parsingRes = requestParsing(_buffer, _requestInfo);
	if ( parsingRes <= 0)
    {
        std::cout << "resquestParsing failed\n\n";
        if (parsingRes == 0)
            return (0);
        if (parsingRes == -1)
        {
            std::cout << "404 notfound\n\n";
            notFound(_requestInfo, _responsContent);
        }
        if (parsingRes == -2)
        {
            std::cout << "403 forbidden\n\n";
            forbidden(_requestInfo, _responsContent);
        }
        return (-1);
    }
	
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
	else if (_requestInfo.at("METHOD") == "DELETE")
		deleteFile(_requestInfo, _responsContent);
	else
    {
        if (_requestInfo.at("METHOD") == "GET" && _requestInfo.at("EXTENSION") == ".php")
        {
            std::cout << "pas" << std::endl;
            CGI(_requestInfo, _responsContent);
        }
        else
    		openFile(_requestInfo, _responsContent);
        
    }
	return (1);
}

int	SERVER::TestServer::_responder(int clientSocket)
{
	RESPONS::CreateRespons	createRespons(_responsContent);
	std::string respons = createRespons.getRespons();
    std::cout << "CLientOcket : "<< clientSocket << "\n\n";
	std::cout << "\n\e[0;93m*****RESPONDER****\n" << respons;
    int sendRes = send(clientSocket, respons.c_str(), respons.size(), 0);
	if (sendRes <= 0)
    {
        if (sendRes == 0)
            std::cerr << "empty respons\n\n";
        else
            std::cerr << "send to client failed";
        _responsContent.clear();
        _requestInfo.clear();
        return (-1);
    }
	std::cout << "send done\n";

	_responsContent.clear();
    _requestInfo.clear();
   // close(clientSocket);
    return (0);
}

void SERVER::TestServer::launch()
{
    std::cout << "\e[0;31m****STARTING*****\e[0m\n";
    std::vector<pollfd> clientSockets;
    int initialSocket = getServerSocket()->getSocketFd();
    pollfd initialSocketPollfd = {0};
    initialSocketPollfd.fd = initialSocket;
    initialSocketPollfd.events = POLLIN;
    initialSocketPollfd.revents = 0;
    clientSockets.push_back(initialSocketPollfd);

    std::cout << "Serveur en attente de connexions..." << std::endl;

    while (true) {
        std::cout << "\n\e[0;32m===== WAITING =====\e[0m\n";
        int activity = poll(&clientSockets[0], clientSockets.size(), -1);
        if (activity < 0) {
            std::cerr << "Erreur lors de l'appel à poll()" << std::endl;
            return;
        }

        if (clientSockets[0].revents & POLLIN) {
            // Nouvelle connexion entrante
            sockaddr_in clientAddress;
            memset(&clientAddress, 0, sizeof(clientAddress));
            socklen_t clientAddressLength = sizeof(clientAddress);
            int newClientSocket = accept(initialSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);
            if (newClientSocket < 0) {
                std::cerr << "Erreur lors de l'acceptation de la connexion" << std::endl;
                continue;
            }

            std::cout << "Nouvelle connexion acceptée : " << newClientSocket << std::endl;

            // Ajout du nouveau client à la liste => changer pour le backlog configFile
            if (clientSockets.size() >= 35) {
                std::cerr << "Le serveur a atteint sa capacité maximale de clients" << std::endl;
                close(newClientSocket);
            } else {
                pollfd newClientPollfd;
                newClientPollfd.fd = newClientSocket;
                newClientPollfd.events = POLLIN;
                newClientPollfd.revents = 0;
                clientSockets.push_back(newClientPollfd);
            }
            continue;
        }

        // Parcourir tous les clients existants
        for (size_t i = 1; i < clientSockets.size(); ++i) {
            if (clientSockets[i].revents & POLLIN) {
                // Données reçues d'un client existant
                char buffer[4096];
                memset(buffer, 0, sizeof(buffer));
                int bytesRead = recv(clientSockets[i].fd, buffer, sizeof(buffer), 0);
                if (bytesRead <= 0) {
                    // Erreur de réception ou connexion fermée
                    if (bytesRead == 0) {
                        std::cout << "Connexion fermée par le client" << std::endl;
                    } else {
                        std::cerr << "Erreur de réception des données" << std::endl;
                    }
                    close(clientSockets[i].fd);
                    clientSockets.erase(clientSockets.begin() + i);
                    --i;
                } else {
                    // Traiter les données reçues du client
                    //std::cout << "Données reçues : " << buffer << std::endl;
                    _buffer = buffer;

                    // Envoyer une réponse au client
                    if (_handler(clientSockets[i].fd) == 0)
                    {
                        // std::cout << "handler == 0\n\n";
                        // close(clientSockets[i].fd);
                        // clientSockets.erase(clientSockets.begin() + i);
                        // --i;
                    }
                    if (_responder(clientSockets[i].fd) < 0)
                    {
                        // close(clientSockets[i].fd);
                        // clientSockets.erase(clientSockets.begin() + i);
                        // --i;
                    }
                    close(clientSockets[i].fd);
                        clientSockets.erase(clientSockets.begin() + i);
                        --i;
                }
                break;
            }
            if (clientSockets[i].revents & POLLOUT)
            {
                std::cout << "\n\nPOULLOUt\n\n";
                close(clientSockets[i].fd);
                clientSockets.erase(clientSockets.begin() + i);
                --i;
            }
        }
         std::cout << "\e[0;36m\n===== DONE =====\e[0m\n";
    }
    for (size_t i = 0; i < clientSockets.size(); ++i) {
        close(clientSockets[i].fd);
    }
    close(initialSocket);
}

// MAP_STRING	&SERVER::TestServer::getMapInfo(void) {
// 	return this->_requestInfo;
// }


// MAP_STRING	&SERVER::TestServer::getMapContent(void) {
// 	return this->_requestContent;
// }

