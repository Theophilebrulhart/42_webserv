/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:54:43 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/03/15 16:17:11 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTSERVER_HPP
# define TESTSERVER_HPP
# include <iostream> 
# include "AServer.hpp"
# include <unistd.h>
# include <vector>
# include "../Parsing/HeadersParsing.hpp"

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
    };
}
#endif