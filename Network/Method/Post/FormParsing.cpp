/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FormParsing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:01:19 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/17 16:20:07 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeadersPost.hpp"

std::string getLastLinePost(std::string& buffer) {
    std::string::size_type pos = buffer.find_last_of('\n');
    if (pos != std::string::npos) {
        // Skip the newline character if it is the last character
        if (pos > 0 && buffer[pos - 1] == '\r') {
            --pos;
        }
		pos++;
        return buffer.substr(pos + 1);
    }
    return buffer;
}

int    formParsing(std::string &buffer, MAP_STRING &info, int socket, MAP_STRING &responsContent, ConfigParser::t_serv &servInfo)
{
    std::string content;
    int         readTest = 1000;
    std::vector<unsigned char>	buf(1000);

    // std::cout << "max size buffer : " << std::stoi(info["CONTENT-LENGTH"]) + buffer.length() << "\n\n";
    
   if ((info.find("CONTENT-TYPE") != info.end()) && (info["CONTENT-TYPE"].find("boundary=") != std::string::npos))
    {
        while (readTest == 1000)
        {
            bzero(buf.data(), 1000);
            readTest = recv(socket, buf.data(), buf.size(), 0);
            if (readTest <= 0)
            {
                if (readTest < 0)
                {
                    std::cout << "Recv problem\n\n";
                    return (-1);
                }
                else if (readTest == 0)
                    std::cout << "Request read\n\n";
            }
            std::string tmp(buf.begin(), buf.end());
            content += tmp;
            if (readTest != 1000)
                break ;
        }
    }
    
    // std::cout << "###### content ########\n\n" << content.substr(0, 1000) << "\n";
    // std::cout << "len :" << content.length() << "\n\n";
    // std::cout << "max :" << std::atoi(servInfo.d_max_body_size.c_str()) << "\n\n";
    if (content.length() > std::atoi(servInfo.d_max_body_size.c_str()))
    {
        std::cout << "body's bigger than max body: check config file\n\n";
        std::string empty;
        setResponsContent(responsContent, "HTTP/1.1", "413 Payload Too Large", empty, empty);
        return (0);
    }
    // std::cout << "body size ok \n\n";
    if (content.length() == 0)
        content = getLastLinePost(buffer);
    // std::cout << "content type : " << info.at("CONTENT-TYPE") << "\n\n";
    if (info.at("CONTENT-TYPE") == "plain/text\r")
    {
        std::cout << "unprocessable\n\n";
        unprocessable(responsContent, servInfo);
        return (0);
    }
    // std::cout << "sending to getFormCalue\n\n";
    getFormValue(content, info, responsContent, servInfo);
    buffer += content;
    return (0);
    // std::cout << "###### bffer ########\n\n" << buffer << "\n";
}