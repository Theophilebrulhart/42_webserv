/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:55:10 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/03 14:33:28 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HeadersGet.hpp"
# include "../Utils.hpp"

void    openFile(MAP_STRING info, MAP_STRING &responsContent)
{
    std::string contentType = contentExtension(info.at("PATH"));
    if (isInternalError(info, responsContent, contentType) < 0)
        return ;
    std::string contentFile = loadContentFile(info.at("PATH"));
    if (contentFile.empty())
    {
        std::string notFound = loadContentFile("/404NotFound.html");
        setResponsContent(responsContent, info.at("PROTOCOL"), "404 Not Found", contentType, notFound);
        return ;
    }
    setResponsContent(responsContent, info.at("PROTOCOL"), "200 OK", contentType, contentFile);
    return ;
}