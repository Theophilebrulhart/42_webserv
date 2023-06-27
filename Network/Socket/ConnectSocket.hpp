/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:38:53 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/03/02 13:35:49 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTSOCKET_HPP
# define CONNECTSOCKET_HPP
# include <iostream> 
# include "ASocket.hpp"

namespace SOCKET
{
    class ConnectSocket : public ASocket
    {
        public:
            ConnectSocket(int domaine, int service, int protocol, int port, u_long interface);
            ~ConnectSocket(void);

            int bindOrConnect(int socketFd, struct sockaddr_in address) const;

        private: 
        
            ConnectSocket(void);
            ConnectSocket(ConnectSocket const &cpy);
            ConnectSocket &operator=(ConnectSocket const &rhs);

    };
}


#endif