/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:55:10 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/06 21:36:20 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HeadersGet.hpp"
# include "../Utils.hpp"

void    openFile(MAP_STRING info, MAP_STRING &responsContent, ConfigParser::t_serv &servInfo)
{
    int routeRet = isRoute(info, responsContent, servInfo);
    if (routeRet < 0)
    {
        if (routeRet == -1)
            return ;
    }
    std::string contentType = contentExtension(info.at("EXTENSION"));
    if (isInternalError(info, responsContent, contentType) < 0)
        return ;
    std::string contentFile = loadContentFile(info.at("PATH"));
    if (contentFile.empty())
    {
        notFound(info, responsContent);
    }
    setResponsContent(responsContent, info.at("PROTOCOL"), "200 OK", contentType, contentFile);
    return ;
}