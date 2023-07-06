/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:57:16 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/06 21:47:07 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestServer.hpp"
#include "../Method/Utils.hpp"

SERVER::TestServer::TestServer(int protocol, int port, int backlog, ConfigParser::t_serv servInfo) : AServer(AF_INET, SOCK_STREAM, protocol, port,
INADDR_ANY, backlog)
{
    _servInfo = servInfo;
    return ;
}

SERVER::TestServer::~TestServer(void)
{
    return ;
}

int	SERVER::TestServer::_handler(int clientSocket)
{
    // std::cout << "\n\nmethod : " << _servInfo.c_routes.at("/").b_methods.front() << "\n\n";
    // std::cout << "\n\nroot : " << _servInfo.c_routes.at("/").a_route << "\n\n";
    // std::cout << "\n\nroot 2: " << _servInfo.c_routes.at("/Pelops.html").a_route << "\n\n";

    int parsingRes = requestParsing(_buffer, _requestInfo);
	if ( parsingRes <= 0)
    {
        std::cout << "resquestParsing failed\n\n";
        if (parsingRes == 0)
            return (0);
        if (parsingRes == -1)
        {
            std::cout << "404 notfound\n\n";
            notFound(_requestInfo, _responsContent);
        }
        if (parsingRes == -2)
        {
            std::cout << "403 forbidden\n\n";
            forbidden(_requestInfo, _responsContent);
        }
        return (-1);
    }
	
	if (_requestInfo.at("METHOD") == "POST")
	{
		try
		{
			_requestInfo.at("CONTENT-TYPE");
			formParsing (_buffer, _requestInfo, clientSocket, _responsContent, _servInfo);
		}
		catch(const std::out_of_range& oor)
		{
			std::cout << "\nNo multipart/form-data\n";
		}
	}
	else if (_requestInfo.at("METHOD") == "DELETE")
		deleteFile(_requestInfo, _responsContent, _servInfo);
	else
    {
        if (_requestInfo.at("METHOD") == "GET" && _requestInfo.at("EXTENSION") == ".php")
        {
            std::cout << "pas" << std::endl;
            CGI(_requestInfo, _responsContent);
        }
        else
    		openFile(_requestInfo, _responsContent, _servInfo);
        
    }
	return (1);
}

int	SERVER::TestServer::_responder(int clientSocket)
{
	RESPONS::CreateRespons	createRespons(_responsContent);
	std::string respons = createRespons.getRespons();
    std::cout << "CLientOcket : "<< clientSocket << "\n\n";
	std::cout << "\n\e[0;93m*****RESPONDER****\n" << respons;
    int sendRes = send(clientSocket, respons.c_str(), respons.size(), 0);
	if (sendRes <= 0)
    {
        if (sendRes == 0)
            std::cerr << "empty respons\n\n";
        else
            std::cerr << "send to client failed";
        _responsContent.clear();
        _requestInfo.clear();
        return (-1);
    }
	std::cout << "send done\n";

	_responsContent.clear();
    _requestInfo.clear();
    return (0);
}
