/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AServer.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:45:35 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/03/07 15:42:33 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AServer.hpp"

SERVER::AServer::AServer(int domain, int service, int protocol,
int port, u_long interface, int backlog)
{
    _serverSocket = new SOCKET::ListenSocket(domain, service, protocol, port, interface, backlog);
    return ;
}

SERVER::AServer::~AServer(void)
{
    return ;
}

SOCKET::ListenSocket *SERVER::AServer::getServerSocket(void) const
{
	return (_serverSocket);
}
