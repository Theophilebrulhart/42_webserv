/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FormParsing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:01:19 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/12 13:27:36 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeadersPost.hpp"

void    formParsing(std::string &buffer, MAP_STRING &info, int socket, MAP_STRING &responsContent, ConfigParser::t_serv &servInfo)
{
    std::string content;
    int         readTest = 1000;
    std::vector<unsigned char>	buf(1000);

    std::cout << "max size buffer : " << std::stoi(info["CONTENT-LENGTH"]) + buffer.length() << "\n\n";
    
   if ((info.find("CONTENT-TYPE") != info.end()) && (info["CONTENT-TYPE"].find("boundary=") != std::string::npos))
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