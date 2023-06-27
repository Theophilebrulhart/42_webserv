/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:51:59 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/03/02 13:35:50 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListenSocket.hpp"

SOCKET::ListenSocket::ListenSocket(int domain, int service, int protocol,
int port, u_long interface, int backlog) : BindSocket(domain, service, protocol,
port, interface)
{
	_backlog = backlog;
	_listenReturn = listening(getSocketFd(), backlog);
	testReturn(_listenReturn);
    return ;
}

SOCKET::ListenSocket::~ListenSocket(void)
{
    return ;
}

int	SOCKET::ListenSocket::listening(int socketFd, int backlog) const
{
	return listen(socketFd, backlog);
}

int SOCKET::ListenSocket::getBacklog(void) const
{
	return (_backlog);
}