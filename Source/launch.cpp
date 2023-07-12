/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:04:55 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/12 09:24:10 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AllHeaders.hpp"
#include <fcntl.h>

int getMapKey(std::map<int, std::vector<int> > &serverClientList, int value, int value_delete)
{
    int i = 0;
    std::cout << "value : " << value << "\n\n";
    for (std::map<int, std::vector<int> >::iterator it = serverClientList.begin(); it != serverClientList.end(); it++)
    {
        std::cout << "it de serveerClientList : " << it->first << "\n\n";
        for (std::vector<int>::iterator itt = it->second.begin(); itt != it->second.end(); itt++)
        {
             std::cout << "it de serveerClientList vector : " << *itt << "\n\n";
            if (*itt == value)
            {
                if (value_delete)
                    it->second.erase(itt);
                std::cout << "return de l'index de server : " << i << "\n\n";
                return (i);
            }
        }
        i++;
    }
    std::cout << "socket pas trouve dans serverClientList\n\n";
    return (-1);
}

SERVER::TestServer  init_server(ConfigParser::t_serv servInfo,  std::vector<int>& serverSockets, std::string port, std::map<int, std::vector<int> > &serverClientList)
{
    SERVER::TestServer serv(0, atoi(port.c_str()), 40, servInfo);
    fcntl(serv.getServerSocket()->getSocketFd(), F_SETFL, O_NONBLOCK);
    serverClientList[serv.getServerSocket()->getSocketFd()];
    serverSockets.push_back(serv.getServerSocket()->getSocketFd());
    
    return serv;
}

void launch(ConfigParser &configInfo)
{
    std::vector<int> serverSockets; // Liste des sockets serveur
    std::vector<int> clientSockets; // Liste des sockets client
    std::vector<SERVER::TestServer> servers;
    std::map<int, std::vector<int> > serverClientList;

    //creer les serveurs et ajouter leur socket a la liste

    for(std::map<std::string, ConfigParser::t_serv>::iterator it = configInfo.servec.begin(); it != configInfo.servec.end(); it++) {
        std::cout << "\e[0;42m\n**********" << it->first <<"**********\e[0m";
        for(size_t i = 0; i < it->second.b_port.size(); i++)
        {
            std::cout << "i i i i : " << i << "\n\n";
            servers.push_back(init_server(it->second, serverSockets, it->second.b_port[i], serverClientList));
        }
         std::cout << "\e[0;42m\n******************************\e[0m\n\n";
    }

    //creation de la structure pollFds pour chaque server
    std::vector<struct pollfd> pollFds;
            std::cout << "serverSocket size FIRST " << serverSockets.size() << "\n\n";

    for (int i = 0; i < serverSockets.size(); i++)
    {
        struct pollfd pfd;
        pfd.fd = serverSockets[i];
        pfd.events = POLLIN;
        pfd.revents = 0;
        pollFds.push_back(pfd);
    }

    std::cout << "\e[0;31m****STARTING*****\e[0m\n";
    std::cout << "Serveur en attente de connexions..." << std::endl;

    while (true) {
        std::cout << "\n\e[0;32m===== WAITING =====\e[0m\n";
        int pollResult = poll(&pollFds[0], pollFds.size(), -1);
        if (pollResult < 0)
        {
            std::cerr << "Erreur lors de l'appel à poll()" << std::endl;
            return;
        }

        //parcourir tous les serveurs pour les nouvelles connexions
        for (int i = 0; i < serverSockets.size(); ++i)
        {
            if (pollFds[i].revents & POLLIN) 
            {
                // Nouvelle connexion entrante
                 struct sockaddr_in clientAddress;
                //memset(&clientAddress, 0, sizeof(clientAddress));
                 socklen_t clientAddressLength = sizeof(clientAddress);
                int clientSocket = accept(serverSockets[i], (struct sockaddr *)&clientAddress, &clientAddressLength);
                std::cout << "serversocket[i] : " << serverSockets[i] << "\n\n";
                 if (clientSocket < 0)
                {
                    std::cerr << "Erreur lors de l'acceptation de la connexion client" << std::endl;
                    return;
                }

                std::cout << "Nouvelle connexion acceptée : " << clientSocket << std::endl;

                // Ajout du nouveau client à la liste => changer pour le backlog configFile
                if (clientSockets.size() >= 35) {
                    std::cerr << "Le serveur a atteint sa capacité maximale de clients" << std::endl;
                    close(clientSocket);
                } else {
                    clientSockets.push_back(clientSocket);
                    struct pollfd pfd;
                    pfd.fd = clientSocket;
                    pfd.events = POLLIN;
                    pfd.revents = 0;
                    pollFds.push_back(pfd);

                    std::cout << "Nouvelle connexion client sut la socket : " << clientSocket << "\n\n";
                    serverClientList[serverSockets[i]].push_back(clientSocket);
                }
            }
        }

        // Parcourir toutes les sockets clients existants pour les donnees recu
        for (int i = serverSockets.size(); i < pollFds.size(); ++i)
        {
            std::cout << "serverSocket size " << serverSockets.size() << "\n\n";
            std::cout << "pollfd size " << pollFds.size() << "\n\n";

           if (pollFds[i].revents & POLLIN)
           {
                // Données reçues d'un client existant
                char buffer[10000];
                memset(buffer, 0, sizeof(buffer));
                int bytesRead = recv(clientSockets[i - serverSockets.size()], buffer, sizeof(buffer), 0);
                std::cout << "clientSocket [i - serversize()] : " << clientSockets[i - serverSockets.size()] << "\n\n";
                std::cout << "buffer \n" << buffer << "\n\n";
                if (bytesRead <= 0)
                {
                    // Erreur de réception ou connexion fermée
                    if (bytesRead == 0) {
                        std::cout << "Connexion fermée par le client" << std::endl;
                    } else {
                        std::cerr << "Erreur de réception des données" << std::endl;
                    }
                    //Fermer le socket client et le supprimer du tableau pollfd
                    getMapKey(serverClientList, clientSockets[i - serverSockets.size()], 1);
                    close(pollFds[i].fd);
                    clientSockets.erase(clientSockets.begin() + i - serverSockets.size());
                    pollFds.erase(pollFds.begin() + i);

                    continue;
                }
                else {
                    // Récupérer l'instance appropriée de TestServer

                    std::cout << "valeur de i : " << i << "\n\n";
                    int serverIndex = getMapKey(serverClientList, clientSockets[i - serverSockets.size()], 0);
                    std::cout << "serverIndex : " << serverIndex << "\n\n";
                    SERVER::TestServer& server = servers[serverIndex]; // Référence à l'instance de TestServer
                    // Traiter les données reçues du client
                    server._buffer = buffer;

                    // Envoyer une réponse au client
                    if (server._handler(pollFds[i].fd) <= 0)
                    {
                        getMapKey(serverClientList, clientSockets[i - serverSockets.size()], 1);
                        close(pollFds[i].fd);
                        clientSockets.erase(clientSockets.begin() + i - serverSockets.size());
                        pollFds.erase(pollFds.begin() + i);
                    }
                    else if (server._responder(pollFds[i].fd) < 0)
                    {
                        getMapKey(serverClientList, clientSockets[i - serverSockets.size()], 1);
                        close(pollFds[i].fd);
                        clientSockets.erase(clientSockets.begin() + i - serverSockets.size());
                        pollFds.erase(pollFds.begin() + i);
                    }
                    else
                    {
                        getMapKey(serverClientList, clientSockets[i - serverSockets.size()], 1);
                        close(pollFds[i].fd);
                        clientSockets.erase(clientSockets.begin() + i - serverSockets.size());
                        pollFds.erase(pollFds.begin() + i);
                    }
                }
                break;
            }
            for (int i = serverSockets.size(); i < pollFds.size(); ++i)
            {
                if (pollFds[i].revents & POLLOUT)
                {
                    std::cout << "\n\nPOULLOUt\n\n";
                    getMapKey(serverClientList, clientSockets[i - serverSockets.size()], 1);
                    close(pollFds[i].fd);
                    clientSockets.erase(clientSockets.begin() + i - serverSockets.size());
                    pollFds.erase(pollFds.begin() + i);
                }
            }
        }
         std::cout << "\e[0;36m\n===== DONE =====\e[0m\n";
    }
}
