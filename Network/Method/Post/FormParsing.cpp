/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FormParsing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:01:19 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/10 23:15:33 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeadersPost.hpp"

int    formParsing(std::string &buffer, MAP_STRING &info, int socket, MAP_STRING &responsContent, ConfigParser::t_serv &servInfo)
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
            // if (readTest <= 0)
            // {
            //     if (readTest < 0)
            //     {
            //         std::cout << "recv a foireeee putain\n\n";
            //         return (-1);
            //     }
            // }
            std::string tmp(buf.begin(), buf.end());
            content += tmp;
            if (readTest != 1000)
                break ;
        }
    }
    
    std::cout << "###### content ########\n\n" << content.substr(0, 1000) << "\n";
    std::cout << "len :" << content.length() << "\n\n";
    std::cout << "max :" << std::atoi(servInfo.d_max_body_size.c_str()) << "\n\n";
    if (content.length() > std::atoi(servInfo.d_max_body_size.c_str()))
    {
        std::cout << "body too long my friends (like my dick ;) )\n\n";
        return (-1);
    }
    getFormValue(content, info, responsContent, servInfo);
    buffer += content;
    return (0);
    // std::cout << "###### bffer ########\n\n" << buffer << "\n";
}