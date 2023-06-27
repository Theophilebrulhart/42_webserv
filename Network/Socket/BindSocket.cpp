/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindSocket.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:09:37 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/03/02 17:10:02 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BindSocket.hpp"

SOCKET::BindSocket::BindSocket(int domaine, int service, int protocol,
int port, u_long interface) : ASocket(domaine, service, protocol, port, interface)
{
    setBindOrConnect(bindOrConnect(getSocketFd(), getAddress()));
	std::cout << "BIND\n";
	testReturn(getBindOrConnect());
    return ;
}

SOCKET::BindSocket::~BindSocket(void)
{
    return ;
}

int	SOCKET::BindSocket::bindOrConnect(int socketFd, struct sockaddr_in address) const
{
	return (bind(socketFd, (struct sockaddr *)&address, sizeof(address)));
}