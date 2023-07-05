/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:04:55 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/05 20:46:42 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AllHeaders.hpp"

void launch()
{
    std::cout << "\e[0;31m****STARTING*****\e[0m\n";
    std::vector<int> serverSockets; // Liste des sockets serveur
    std::vector<int> clientSockets; // Liste des sockets client
    std::vector<SERVER::TestServer> servers;

    //creer les serveurs et ajouter leur socket a la liste
    SERVER::TestServer t(0, 80, 40);
    serverSockets.push_back(t.getServerSocket()->getSocketFd());
    servers.push_back(t);
    SERVER::TestServer a(0, 400, 40);
    serverSockets.push_back(a.getServerSocket()->getSocketFd());
    servers.push_back(a);
    SERVER::TestServer b(0, 401, 40);
    serverSockets.push_back(b.getServerSocket()->getSocketFd());
    servers.push_back(b);
    SERVER::TestServer c(0, 402, 40);
    serverSockets.push_back(c.getServerSocket()->getSocketFd());
    servers.push_back(c);
    SERVER::TestServer d(0, 403, 40);
    serverSockets.push_back(d.getServerSocket()->getSocketFd());
    servers.push_back(d);
    
    
    //creation de la structure pollFds pour chaque server
    std::vector<struct pollfd> pollFds;
    for (int i = 0; i < serverSockets.size(); ++i)
    {
        struct pollfd pfd;
        pfd.fd = serverSockets[i];
        pfd.events = POLLIN;
        pfd.revents = 0;
        pollFds.push_back(pfd);
    }

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
            if (pollFds[i].revents & POLLIN) \
            {
                // Nouvelle connexion entrante
                 struct sockaddr_in clientAddress;
                //memset(&clientAddress, 0, sizeof(clientAddress));
                 socklen_t clientAddressLength = sizeof(clientAddress);
                int clientSocket = accept(serverSockets[i], (struct sockaddr *)&clientAddress, &clientAddressLength);
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

                    std::cout << "Nouvelle connexion client" << std::endl;
                }
            }
        }

        // Parcourir toutes les sockets clients existants pour les donnees recu
        for (int i = serverSockets.size(); i < pollFds.size(); ++i)
        {
           if (pollFds[i].revents & POLLIN)
           {
                // Données reçues d'un client existant
                char buffer[4096];
                memset(buffer, 0, sizeof(buffer));
               int bytesRead = recv(clientSockets[i - serverSockets.size()], buffer, sizeof(buffer), 0);
                if (bytesRead <= 0) {
                    // Erreur de réception ou connexion fermée
                    if (bytesRead == 0) {
                        std::cout << "Connexion fermée par le client" << std::endl;
                    } else {
                        std::cerr << "Erreur de réception des données" << std::endl;
                    }
                    //Fermer le socket client et le supprimer du tableau pollfd
                    close(pollFds[i].fd);
                    clientSockets.erase(clientSockets.begin() + i - serverSockets.size());
                    pollFds.erase(pollFds.begin() + i);

                    continue;
                }
                else {
                    // Récupérer l'instance appropriée de TestServer
                    int serverIndex = i - serverSockets.size();
                    SERVER::TestServer& server = servers[serverIndex]; // Référence à l'instance de TestServer
                    // Traiter les données reçues du client
                    server._buffer = buffer;

                    // Envoyer une réponse au client
                    if (server._handler(pollFds[i].fd) == 0)
                    {
                        // std::cout << "handler == 0\n\n";
                        // close(clientSockets[i].fd);
                        // clientSockets.erase(clientSockets.begin() + i);
                        // --i;
                    }
                    if (server._responder(pollFds[i].fd) < 0)
                    {
                        // close(clientSockets[i].fd);
                        // clientSockets.erase(clientSockets.begin() + i);
                        // --i;
                    }
                    close(pollFds[i].fd);
                    clientSockets.erase(clientSockets.begin() + i - serverSockets.size());
                    pollFds.erase(pollFds.begin() + i);
                }
                break;
            }
            for (int i = serverSockets.size(); i < pollFds.size(); ++i)
            {
                if (pollFds[i].revents & POLLOUT)
                {
                    std::cout << "\n\nPOULLOUt\n\n";
                    close(pollFds[i].fd);
                    clientSockets.erase(clientSockets.begin() + i - serverSockets.size());
                    pollFds.erase(pollFds.begin() + i);
                }
            }
        }
         std::cout << "\e[0;36m\n===== DONE =====\e[0m\n";
    }
}









// while (true) {
//         // ...
//         // Reste du code
//         // ...

//         // Parcourir toutes les sockets clients existantes pour les données reçues
//         for (int i = serverSockets.size(); i < pollFds.size(); ++i)
//         {
//             if (pollFds[i].revents & POLLIN)
//             {
//                 // Données reçues d'un client existant
//                 char buffer[4096];
//                 memset(buffer, 0, sizeof(buffer));
//                 int bytesRead = recv(clientSockets[i - serverSockets.size()], buffer, sizeof(buffer), 0);
//                 if (bytesRead <= 0) {
//                     // ...
//                     // Reste du code
//                     // ...

//                     continue;
//                 } else {
//                     // Traiter les données reçues du client

//                     // Récupérer l'instance appropriée de TestServer
//                     int serverIndex = i - serverSockets.size();
//                     SERVER::TestServer& server = t[serverIndex]; // Référence à l'instance de TestServer
//                     // ou
//                     SERVER::TestServer* serverPtr = &t[serverIndex]; // Pointeur vers l'instance de TestServer

//                     // Utiliser les membres de l'instance de TestServer
//                     server._buffer = buffer;
//                     // ou
//                     serverPtr->_buffer = buffer;

//                     if (server._handler(pollFds[i].fd) == 0)
//                     {
//                         // ...
//                         // Reste du code
//                         // ...
//                     }
//                     if (server._responder(pollFds[i].fd) < 0)
//                     {
//                         // ...
//                         // Reste du code
//                         // ...
//                     }
//                     // ...
//                     // Reste du code
//                     // ...
//                 }
//                 break;
//             }
//             // ...
//             // Reste du code
//             // ...
//         }
//         std::cout << "\e[0;36m\n===== DONE =====\e[0m\n";
//     }
// }