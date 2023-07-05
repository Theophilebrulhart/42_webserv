/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:54:43 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/05 13:26:59 by pyammoun         ###   ########.fr       */
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
            TestServer();
            ~TestServer(void);
            
            void    launch(void);
            

        private:

            std::string		_buffer;
            int				_newSocket;
            int  			_handler(int clientSocket);
            int     		_responder(int clientSocket);
			MAP_STRING		_requestInfo;
            MAP_STRING      _responsContent;
            std::vector<int> _clientSockets;
    };
}
#endif