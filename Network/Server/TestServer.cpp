/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:57:16 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/17 15:23:59 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestServer.hpp"
#include "../Method/HeadersMethod.hpp"

SERVER::TestServer::TestServer(int protocol, int port, int backlog) : AServer(AF_INET, SOCK_STREAM, protocol, port,
INADDR_ANY, backlog)
{
    _port = port;
    return ;
}

SERVER::TestServer::~TestServer(void)
{
    return ;
}

int getHost(std::map<std::string, ConfigParser::t_serv> &servers, std::string host, MAP_STRING &responsContent, ConfigParser::t_serv &servInfo)
{
    std::string shortHost = host.substr(0, host.find(":"));

    for (std::map<std::string, ConfigParser::t_serv>::iterator it = servers.begin(); it != servers.end(); it++)
    {
        if (shortHost == it->second.g_hostname) {
            std::cout << "prout" << std::endl;
            servInfo = it->second;
            return (1);
        }
    }
    std::cout << "prout2" << std::endl;
    std::cout << "t_serv non trouve\n\n";
    
    
    return(0);
}

int	SERVER::TestServer::_handler(int clientSocket)
{
    int parsingRes = requestParsing(_buffer, _requestInfo);
    if (getHost(_servInfos, _requestInfo["HOST"], _responsContent, _servInfo) == 0)
        return (-1);
    // if (_requestInfo["PATH"] == "/favicon.ico")
    //     return -1;
	if ( parsingRes <= 0)
    {
        std::cout << "resquestParsing failed\n\n";
        if (parsingRes == 0)
            return (0);
        if (parsingRes == -1)
        {
            std::cout << "404 notfound\n\n";
            notFound(_responsContent);
        }
        if (parsingRes == -2)
        {
            std::cout << "403 forbidden\n\n";
            forbidden(_responsContent);
        }
        return (-1);
    }
	
	if (_requestInfo.at("METHOD") == "POST")
	{
        if (_requestInfo.at("CONTENT-TYPE") == "application/x-www-form-urlencoded\r")
        {
            if (isRoute(_requestInfo, _responsContent, _servInfo).d_root.empty())
            {
                std::cout << "empty route" << std::endl;
                return 1;
            }
            CGI(_requestInfo, _responsContent, _servInfo);
            return 1;
        }
        // std::cout << _requestInfo.at("CONTENT-TYPE") << std::endl;
		try
		{
			_requestInfo.at("CONTENT-TYPE");
			if (formParsing (_buffer, _requestInfo, clientSocket, _responsContent, _servInfo) < 0)
                return (-1);
		}
		catch(const std::out_of_range& oor)
		{
			std::cout << "\nNo Content\n";
		}
	}
	else if (_requestInfo.at("METHOD") == "DELETE")
		deleteFile(_requestInfo, _responsContent, _servInfo);
	else
    	openFile(_requestInfo, _responsContent, _servInfo);
	return (1);
}

int	SERVER::TestServer::_responder(int clientSocket)
{
	RESPONS::CreateRespons	createRespons(_responsContent);
	std::string respons = createRespons.getRespons();
    // std::cout << "CLientOcket : "<< clientSocket << "\n\n";
	// std::cout << "\n\e[0;93m*****RESPONDER****\n" << respons;
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
	// std::cout << "send done\n";

	_responsContent.clear();
    _requestInfo.clear();
    return (0);
}
