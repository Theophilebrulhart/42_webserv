/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:55:10 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/17 16:04:41 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HeadersGet.hpp"

void    openFile(MAP_STRING info, MAP_STRING &responsContent, ConfigParser::t_serv &servInfo)
{
    // std::cout << "openFile\n\n";
    std::cout << "serve in fo dans openFile 0 : " << servInfo.a_server_names[0]; 
    ConfigParser::t_route route = isRoute(info, responsContent, servInfo);
    if (route.a_route.empty())
    {
        std::cout << "empty iiuuuiuui \n\n";
            return ;
    }
    std::string path = info.at("PATH");
    int isDirectoryTmp = isDir(route.d_root.substr(1) + info.at("PATH").substr(1));
   if (isDirectoryTmp)
    {
        // std::cout << "Is directory with / at the end ? \n\n";
            char lastChar = path[path.length() - 1];
            if (lastChar != '/')
            {
                std::cout << "no / at the end of this directory\n\n";
                redirection(responsContent, "Location: " + path + "/");
                return ;
            }
    }
    if (info.at("METHOD") == "GET")
    {
        // std::cout << "method get\n\n";
        try
        {
            if (info.at("EXTENSION") == ".php")
            {
                CGI(info, responsContent, servInfo);
                return ;
            }
        }
        catch(const std::out_of_range& oor)
        {
            std::cout << "\nNo php extension\n";
        }
    }
    std::string contentType;
    try
    {
        contentType = contentExtension(info.at("EXTENSION"));
        if (isInternalError(info, responsContent, contentType) < 0)
            return ;
    }
    catch (const std::out_of_range of)
    {
        std::cout << "no extension\n";
    }
    std::string contentFile = getFileToLoad(info, route);
    if (contentFile.empty())
    {
        notFound(responsContent, servInfo);
    }
    setResponsContent(responsContent, info.at("PROTOCOL"), "200 OK", contentType, contentFile);
    return ;
}