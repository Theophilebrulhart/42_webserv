/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:54:43 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/30 16:02:21 by tbrulhar         ###   ########.fr       */
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
            void			_accepter(void);
            void  			_handler(int clientSocket);
            void    		_responder(int clientSocket);
			MAP_STRING		_requestInfo;
            MAP_STRING      _responsContent;
            std::vector<int> _clientSockets;
    };
}
#endif