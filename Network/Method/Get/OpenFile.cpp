/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:55:10 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/07 18:24:13 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HeadersGet.hpp"

void    openFile(MAP_STRING info, MAP_STRING &responsContent, ConfigParser::t_serv &servInfo)
{
    std::cout << "openFile\n\n";
    ConfigParser::t_route route = isRoute(info, responsContent, servInfo);
    if (info.at("METHOD") == "GET")
    {
        std::cout << "method get\n\n";
        try
        {
            if (info.at("EXTENSION") == ".php")
                CGI(info, responsContent);
        }
        catch(const std::out_of_range& oor)
        {
            std::cout << "\nNo php extension\n";
        }
    }
    if (route.a_route.empty())
    {
        std::cout << "empty \n\n";
            return ;
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
        notFound(responsContent);
    }
    setResponsContent(responsContent, info.at("PROTOCOL"), "200 OK", contentType, contentFile);
    return ;
}