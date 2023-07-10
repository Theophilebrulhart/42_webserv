/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FormParsing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:01:19 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/10 16:48:25 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeadersPost.hpp"

void    formParsing(std::string &buffer, MAP_STRING &info, int socket, MAP_STRING &responsContent, ConfigParser::t_serv &servInfo)
{
    std::string content;
    int         readTest = 1000;
    std::vector<unsigned char>	buf(1000);
    
    // if (info.at("EXTENSION") == ".php")
    // {
    //     char buffer[1000];
    //     std::string requestContent;

    //     size_t bytesRead;
    //     while ((bytesRead = recv(socket, buffer, sizeof(buffer), 0)) > 0) 
    //     {
    //         requestContent.append(buffer, bytesRead);
    //         // Check if the request has ended (e.g., double line break "\r\n\r\n")
    //         if (requestContent.find("\r\n\r\n") != std::string::npos) {
    //             break;
    //     }
    // }
    // std::cout << "prouti :" << requestContent << std::endl;
    // }
    // if (info.at("EXTENSION") == ".php")
    // {
    //     while (readTest == 1000)
    //     {
    //         bzero(buf.data(), 1000);
    //         readTest = recv(socket, buf.data(), buf.size(), 0);
    //         //std::cout << "recv : " << readTest << "\n";
    //         std::string tmp(buf.begin(), buf.end());
    //         content += tmp;
    //         if (readTest != 1000)
    //             break ;
    //     }
    // } 
    if (info.at("CONTENT-TYPE").find("boundary=") != std::string::npos)
    {
        while (readTest == 1000)
        {
            bzero(buf.data(), 1000);
            readTest = recv(socket, buf.data(), buf.size(), 0);
            //std::cout << "recv : " << readTest << "\n";
            std::string tmp(buf.begin(), buf.end());
            content += tmp;
            if (readTest != 1000)
                break ;
        }
    }
    
    std::cout << "###### content ########\n\n" << content.substr(0, 1000) << "\n";
    getFormValue(content, info, responsContent, servInfo);
    buffer += content;
    // std::cout << "###### bffer ########\n\n" << buffer << "\n";
}