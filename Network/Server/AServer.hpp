/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AServer.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:41:59 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/03 11:27:10 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASERVER_HPP
# define ASERVER_HPP
# include <iostream>
# include <sys/socket.h>
# include "../Socket/HeadersSocket.hpp"
# include <map>
# define MAP_STRING std::map<std::string, std::string>

namespace   SERVER
{
    class AServer
    {
        public:
            AServer(int domain, int service, int protocol, int port,
                    u_long interface, int backlog);
            ~AServer(void);

            virtual void    		launch(void) = 0;
            SOCKET::ListenSocket    *getServerSocket(void) const;
			
        private:

            SOCKET::ListenSocket    *_serverSocket;
            virtual int    _handler(int clientSocket) = 0;
            virtual int    _responder(int clientSocket) = 0;
    };
}

#endif