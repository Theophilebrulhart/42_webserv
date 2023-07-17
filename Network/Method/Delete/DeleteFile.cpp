/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteFile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:25:27 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/17 17:55:46 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HeadersDelete.hpp"

void deleteFile(MAP_STRING &info, MAP_STRING &responsContent, ConfigParser::t_serv servInfo)
{
    ConfigParser::t_route route = isRoute(info, responsContent, servInfo);
    if (route.a_route.empty())
    {
        std::cout << "empty \n\n";
            return ;
    }
    std::string body;
    std::string fileToDelete;
    fileToDelete = route.d_root.substr(1) + info.at("PATH").substr(1);
    std::string contentType = contentExtension(info.at("PATH"));
    if (isInternalError(info, responsContent, contentType) < 0)
        return ;
    if (std::remove(fileToDelete.c_str()) != 0)
    {
        std::perror(("Failed to delete the file located at " + fileToDelete).c_str());
        setResponsContent(responsContent, info.at("PROTOCOL"), "400 Not Found", contentType, body);
		return ;
    }
   setResponsContent(responsContent, info.at("PROTOCOL"), "204 No Content", contentType, body);
   return ;
}