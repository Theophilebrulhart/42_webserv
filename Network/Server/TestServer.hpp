/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:54:43 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/06 16:52:36 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTSERVER_HPP
# define TESTSERVER_HPP
# include <iostream> 
# include "AServer.hpp"
# include <unistd.h>
# include <vector>
# include <sys/types.h>
# include <sys/select.h>
# include <sys/time.h>
# include <cstdlib>
# include <cstring>
# include <sys/socket.h>
# include <netinet/in.h>
#  include <poll.h>

# include "../Parsing/HeadersParsing.hpp"
# include "../Method/HeadersMethod.hpp"
# include "../Respons/HeadersRespons.hpp"
# include "../CGI/CGI.hpp"



namespace   SERVER
{
    class TestServer : public AServer
    {
        public:
            TestServer(int protocol, int port, int backlog, ConfigParser::t_serv servInfo);
            ~TestServer(void);
            
            int  			        _handler(int clientSocket);
            int     		        _responder(int clientSocket);
            std::string		        _buffer;
            ConfigParser::t_serv    _servInfo;

        private:
            TestServer();

            int				_newSocket;
            
			MAP_STRING		_requestInfo;
            MAP_STRING      _responsContent;
            std::vector<int> _clientSockets;
    };
}
#endif