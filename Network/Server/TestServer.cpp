/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:57:16 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/30 14:40:55 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestServer.hpp"

SERVER::TestServer::TestServer() : AServer(AF_INET, SOCK_STREAM, 0, 80,
INADDR_ANY, 35)
{
	launch();
    return ;
}

SERVER::TestServer::~TestServer(void)
{
    return ;
}

void    SERVER::TestServer::_accepter(void)
{
    struct  sockaddr_in address = getServerSocket()->getAddress();
    int     addrlen = sizeof(address);
	std::vector<char>	buf(1000);

    _newSocket = accept(getServerSocket()->getSocketFd(), (struct sockaddr *)&address,
                        (socklen_t *)&addrlen);
	if (_newSocket < 0)
	{
		std::cerr << "Failed to accept socket\n";
		exit (EXIT_FAILURE);
	}
	bzero(buf.data(), buf.size());
	if (recv(_newSocket, buf.data(), buf.size(), 0) < 0)
	{
		std::cerr << "Failed recv\n";
		exit (EXIT_FAILURE);
	}
	std::string str(buf.begin(), buf.end());
	_buffer = str;
	//std::cout << _buffer << std::endl;
	std::cout << "\naccepter end\n\n";
	return ;
}

void	SERVER::TestServer::_handler(void)
{
	//std::cout << "\ntests\n";
	requestParsing(_buffer, _requestInfo);
	
	if (_requestInfo.at("METHOD") == "POST")
	{
		try
		{
			_requestInfo.at("CONTENT-TYPE");
			formParsing (_buffer, _requestInfo, _newSocket, _responsContent);
		}
		catch(const std::out_of_range& oor)
		{
			std::cout << "\nNo multipart/form-data\n";
		}
	}
	if (_requestInfo.at("METHOD") == "DELETE")
	{
		try
		{
			_requestInfo.at("CONTENT-TYPE");
			deleteFile(_requestInfo, _responsContent);
		}
		catch(const std::out_of_range& oor)
		{
			std::cout << "\nNo multipart/form-data\n";
		}
	}
	if (_requestInfo.at("METHOD") == "GET")
		openFile(_requestInfo, _responsContent);
	return ;
}

void	SERVER::TestServer::_responder(void)
{
	RESPONS::CreateRespons	createRespons(_responsContent);
	std::string respons = createRespons.getRespons();
	std::cout << "\n\e[0;93m*****RESPONDER****\n" << respons;
	send(_newSocket, respons.c_str(), respons.size(), 0);
	//std::cout << "send done\n";
	close(_newSocket);

	std::map<std::string, std::string>::const_iterator it;
    for (it = _responsContent.begin(); it != _responsContent.end(); )
	{
		_responsContent.erase(it++);
	}
	return ;
}

void	SERVER::TestServer::launch(void)
{
	std::cout << "\e[0;31m****STARTING*****\e[0m\n";
	while (1)
	{
		std::cout << "\n\e[0;32m===== WAITING =====\e[0m\n";
		_accepter();
		std::cout << "\ntests1\n";
		_handler();
		_responder();
		std::cout << "\e[0;36m\n===== DONE =====\e[0m\n";
	}
	return ;
}

MAP_STRING	&SERVER::TestServer::getMapInfo(void) {
	return this->_requestInfo;
}


MAP_STRING	&SERVER::TestServer::getMapContent(void) {
	return this->_requestContent;
}

