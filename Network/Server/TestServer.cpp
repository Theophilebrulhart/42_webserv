/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:57:16 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/30 16:35:15 by tbrulhar         ###   ########.fr       */
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
		deleteFile(_requestInfo, _responsContent);
	if (_requestInfo.at("METHOD") == "GET")
		openFile(_requestInfo, _responsContent);
	return ;
}

void	SERVER::TestServer::_responder(int clientSocket)
{
	RESPONS::CreateRespons	createRespons(_responsContent);
	std::string respons = createRespons.getRespons();
    //std::cout << "CLientOcket : "<< clientSocket << "\n\n";
	std::cout << "\n\e[0;93m*****RESPONDER****\n" << respons;
	send(clientSocket, respons.c_str(), respons.size(), 0);
	//std::cout << "send done\n";

	_responsContent.clear();
    _requestInfo.clear();
	return ;
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
    clientSockets.push_back(initialSocketPollfd); // Ajout du socket du serveur à la liste

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
                clientSockets.push_back(newClientPollfd); // Ajout du nouveau client à la liste
            }

            // Ignorer les autres sockets dans cette itération
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
                    --i; // Réduire l'indice après la suppression d'un élément
                } else {
                    // Traiter les données reçues du client
                    std::cout << "Données reçues : " << buffer << std::endl;
                    _buffer = buffer;

                    // Envoyer une réponse au client (exemple)
                    _handler(clientSockets[i].fd);
                    _responder(clientSockets[i].fd);
                }

                // Ignorer les autres sockets dans cette itération
                break;
            }
        }
         std::cout << "\e[0;36m\n===== DONE =====\e[0m\n";
    }

    // Fermer tous les sockets clients restants
    for (size_t i = 0; i < clientSockets.size(); ++i) {
        close(clientSockets[i].fd);
    }

    // Fermer le socket du serveur
    close(initialSocket);
}


// void SERVER::TestServer::launch(void)
// {
//     std::cout << "\e[0;31m****STARTING*****\e[0m\n";
//     int initialSocket = getServerSocket()->getSocketFd();
//     std::cout << "\e[0;31minitialsocket " << initialSocket << "\e[0m\n\n";

//     fd_set readfds, writefds;
//     FD_ZERO(&readfds);
//     FD_ZERO(&writefds);
//     FD_SET(initialSocket, &readfds);
//     int maxfd = initialSocket;

//     while (true)
//     {
//         std::cout << "\n\e[0;32m===== WAITING =====\e[0m\n";
//         fd_set tempReadFds = readfds;
//         fd_set tempWriteFds = writefds;

//         // Utilisation de select() pour attendre des événements sur les sockets
//         int activity = select(maxfd + 1, &tempReadFds, &tempWriteFds, NULL, NULL);

//         if (activity == -1)
//         {
//             std::perror("Erreur lors de l'appel à select().");
//             close(initialSocket);
//             return;
//         }

//         // Mettre à jour l'ensemble writefds
//         writefds = tempWriteFds;

//         // Nouvelle connexion entrante
//         if (FD_ISSET(initialSocket, &tempReadFds))
//         {
//             // Accepter la nouvelle connexion
//             int clientSocket = accept(initialSocket, NULL, NULL);
//             std::cout << "\e[0;31mnouvelle connexion : " << clientSocket << "\e[0m\n";
//             if (clientSocket == -1)
//             {
//                 std::cerr << "Erreur lors de l'acceptation de la connexion." << std::endl;
//                 close(initialSocket);
//                 return;
//             }

//             // Ajouter le socket client à la liste
//             _clientSockets.push_back(clientSocket);
//             std::cout << "Nouvelle connexion entrante. Client ID: " << clientSocket << std::endl;

//             // Mettre à jour le descripteur de fichier maximal
//             if (clientSocket > maxfd)
//                 maxfd = clientSocket;

//             // Ajouter le socket client à l'ensemble des descripteurs de fichiers en lecture et en écriture
//             FD_SET(clientSocket, &readfds);
//             FD_SET(clientSocket, &writefds);
//         }

//         // Vérifier les sockets des clients existants pour les données entrantes et sortantes
//         for (size_t i = 0; i < _clientSockets.size(); ++i)
//         {
//             int clientSocket = _clientSockets[i];

//             if (FD_ISSET(clientSocket, &tempReadFds))
//             {
//                 char buffer[4096];
//                 memset(buffer, 0, sizeof(buffer));

//                 // Lire les données reçues
//                 ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
//                 if (bytesRead == -1)
//                 {
//                     std::cerr << "Erreur lors de la réception des données." << std::endl;
//                     close(initialSocket);
//                     return;
//                 }

//                 if (bytesRead == 0)
//                 {
//                     // Le client a fermé la connexion
//                     std::cout << "Connexion fermée. Client ID: " << clientSocket << std::endl;
//                     close(clientSocket);
//                     FD_CLR(clientSocket, &readfds);
//                     FD_CLR(clientSocket, &writefds);
//                     _clientSockets.erase(_clientSockets.begin() + i);
//                     --i;
//                 }
//                 else
//                 {
//                     // Afficher les informations du socket client
//                     std::cout << "Client ID: " << clientSocket << std::endl;

//                     // Faire quelque chose avec les données reçues
//                     _buffer = buffer;
//                     _handler(clientSocket);
//                 }
//             }

//             if (FD_ISSET(clientSocket, &writefds))
//             {
//                 std::cout << "Socket prête à l'écriture. Client ID: " << clientSocket << std::endl;
//                 _responder(clientSocket);
//             }
//         }

//         std::cout << "\e[0;36m\n===== DONE =====\e[0m\n";
//     }

//     // Fermer le socket du serveur
//     close(initialSocket);
//     return;
// }
