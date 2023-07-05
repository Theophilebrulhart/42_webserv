#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>

#define MAX_CLIENTS 10
#define MAX_BUFFER_SIZE 1024

void launch()
{
    std::vector<int> serverSockets; // Liste des sockets serveur
    std::vector<int> clientSockets; // Liste des sockets client

    // Création des sockets serveur
    for (int i = 0; i < serverSockets.size(); ++i)
    {
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0)
        {
            std::cerr << "Erreur lors de la création du socket serveur" << std::endl;
            return;
        }

        // Configuration du socket serveur
        struct sockaddr_in serverAddress;
        memset(&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(8080); // Port d'écoute

        // Lier le socket serveur à l'adresse locale
        if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        {
            std::cerr << "Erreur lors de la liaison du socket serveur" << std::endl;
            return;
        }

        // Mettre le socket serveur en mode écoute
        if (listen(serverSocket, 5) < 0)
        {
            std::cerr << "Erreur lors de la mise en écoute du socket serveur" << std::endl;
            return;
        }

        serverSockets.push_back(serverSocket);
    }

    std::vector<struct pollfd> pollFds;
    for (int i = 0; i < serverSockets.size(); ++i)
    {
        struct pollfd pfd;
        pfd.fd = serverSockets[i];
        pfd.events = POLLIN;
        pfd.revents = 0;
        pollFds.push_back(pfd);
    }

    char buffer[MAX_BUFFER_SIZE];

    while (true)
    {
        int pollResult = poll(&pollFds[0], pollFds.size(), -1);
        if (pollResult < 0)
        {
            std::cerr << "Erreur lors de l'appel à poll()" << std::endl;
            return;
        }

        // Vérifier les sockets serveur pour les nouvelles connexions
        for (int i = 0; i < serverSockets.size(); ++i)
        {
            if (pollFds[i].revents & POLLIN)
            {
                // Accepter la nouvelle connexion
                struct sockaddr_in clientAddress;
                socklen_t clientAddressLength = sizeof(clientAddress);
                int clientSocket = accept(serverSockets[i], (struct sockaddr *)&clientAddress, &clientAddressLength);
                if (clientSocket < 0)
                {
                    std::cerr << "Erreur lors de l'acceptation de la connexion client" << std::endl;
                    return;
                }

                // Ajouter le socket client à la liste
                clientSockets.push_back(clientSocket);

                // Ajouter le socket client au tableau pollfd
                struct pollfd pfd;
                pfd.fd = clientSocket;
                pfd.events = POLLIN;
                pfd.revents = 0;
                pollFds.push_back(pfd);

                std::cout << "Nouvelle connexion client" << std::endl;
            }
        }

        // Vérifier les sockets clients pour les données reçues
        for (int i = serverSockets.size(); i < pollFds.size(); ++i)
        {
            if (pollFds[i].revents & POLLIN)
            {
                int bytesRead = recv(pollFds[i].fd, buffer, sizeof(buffer), 0);
                if (bytesRead <= 0)
                {
                    // Erreur de lecture ou la connexion a été fermée
                    if (bytesRead == 0)
                    {
                        std::cout << "Déconnexion client" << std::endl;
                    }
                    else
                    {
                        std::cerr << "Erreur de lecture du socket client" << std::endl;
                    }

                    // Fermer le socket client et le supprimer du tableau pollfd
                    close(pollFds[i].fd);
                    clientSockets.erase(clientSockets.begin() + i - serverSockets.size());
                    pollFds.erase(pollFds.begin() + i);

                    continue;
                }

                // Traiter les données reçues
                std::cout << "Données reçues du client: " << std::string(buffer, bytesRead) << std::endl;

                // Répondre au client (exemple simple)
                const char *response = "Message reçu";
                send(pollFds[i].fd, response, strlen(response), 0);
            }
        }
    }
}
