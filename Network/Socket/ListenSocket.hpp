/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:50:27 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/03/02 13:44:58 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTENSOCKET_HPP
# define LISTENSOCKET_HPP
# include <iostream> 
# include "BindSocket.hpp"

namespace SOCKET
{
    class ListenSocket : public BindSocket
    {
        public:
            ListenSocket(int domain, int service, int protocol, int port,
                            u_long interface, int backlog);
            ~ListenSocket(void);

            int listening(int socketFd, int backlog) const;
            int  getBacklog(void) const;

        private:

            int _backlog;
            int _listenReturn;

            ListenSocket(void);
            //ListenSocket(ListenSocket const &cpy);
            ListenSocket &operator=(ListenSocket const &rhs);
    };
}



#endif