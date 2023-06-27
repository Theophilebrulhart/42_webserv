/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:41:25 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/03/02 17:10:22 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectSocket.hpp"

SOCKET::ConnectSocket::ConnectSocket(int domain, int service, int protocol,
int port, u_long interface) : ASocket(domain, service, protocol, port, interface)
{
    setBindOrConnect(bindOrConnect(getSocketFd(), getAddress()));
	std::cout << "CONNECT\n";
	testReturn(getBindOrConnect());
    return ;
}

SOCKET::ConnectSocket::~ConnectSocket(void)
{
    return ;
}

int	SOCKET::ConnectSocket::bindOrConnect(int socketFd, struct sockaddr_in address) const
{
	return (bind(socketFd, (struct sockaddr *)&address, sizeof(address)));
}