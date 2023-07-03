/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:54:43 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/30 15:05:33 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTSERVER_HPP
# define TESTSERVER_HPP
# include <iostream> 
# include "AServer.hpp"
# include <unistd.h>
# include <vector>
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

            std::string			_buffer;
            int				_newSocket;
            void			_accepter(void);
            void  			_handler(void);
            void    		_responder(void);
			MAP_STRING		_requestInfo;
            MAP_STRING      _responsContent;
    };
}
#endif