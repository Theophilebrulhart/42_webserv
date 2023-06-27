/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:20:21 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/03/02 17:12:24 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASOCKET_HPP
# define ASOCKET_HPP
# include <iostream>
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdio.h>
# include <unistd.h>

namespace SOCKET
{
    class ASocket
    {
        public:
            
            ASocket(int domain, int service, int protocol, int port, u_long interface);
            ~ASocket(void);

            void    testReturn(int value) const;
            int     getSocketFd(void) const;
            int     getBindOrConnect(void) const;
			struct sockaddr_in getAddress(void) const;

			void	setBindOrConnect(int value); 

            virtual int    bindOrConnect(int socketFd, struct sockaddr_in address) const = 0;

        private:

            int                 _socketFd;
            int                 _bindOrConnect;
            struct  sockaddr_in _address;
        
            ASocket(void);
            //ASocket(ASocket const &cpy);
            ASocket &operator=(ASocket const &rhs);

    };
}


#endif