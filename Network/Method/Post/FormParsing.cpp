/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formParsing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:01:19 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/28 15:06:24 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeadersPost.hpp"

void    formParsing(std::string &buffer, MAP_STRING &info, int socket)
{
    std::string content;
    int         readTest = 1000;
    std::vector<unsigned char>	buf(1000);
    
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

    getFormValue(content, info);
    buffer += content;
    // std::cout << "###### bffer ########\n\n" << buffer << "\n";
}