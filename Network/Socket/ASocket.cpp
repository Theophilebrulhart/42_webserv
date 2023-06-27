/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:29:26 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/03/06 11:00:54 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASocket.hpp"


SOCKET::ASocket::ASocket(int domain, int service, int protocol,
int port, u_long interface)
{
    _socketFd = socket(domain, service, protocol);
    std::cout << "SOCKET FD\n";
    testReturn(_socketFd);
    _address.sin_family = domain;
    _address.sin_addr.s_addr = interface;
    _address.sin_port = htons(port);
   return ;
}

SOCKET::ASocket::~ASocket(void)
{
    return ;
}

void    SOCKET::ASocket::testReturn(int value) const
{
    if (value < 0)
    {
        std::cerr << "Return function failed : " << std::endl;
        close(_socketFd);
        exit(EXIT_FAILURE);
    }
    return ;
}

int SOCKET::ASocket::getSocketFd(void) const
{
    return (_socketFd);
}

int SOCKET::ASocket::getBindOrConnect(void) const
{
    return (_bindOrConnect);
}

struct sockaddr_in SOCKET::ASocket::getAddress(void) const
{
    return (_address);
}

void    SOCKET::ASocket::setBindOrConnect(int value)
{
    _bindOrConnect = value;
    return ;
}