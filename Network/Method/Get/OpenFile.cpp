/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:55:10 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/29 15:30:58 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HeadersGet.hpp"
# include "../Utils.hpp"

void    openFile(MAP_STRING info, MAP_STRING &responsContent)
{
    std::string contentType = contentExtension(info.at("PATH"));
    std::string contentFile = loadContentFile(info.at("PATH"));
	if (contentType == "Not supported")
    {
        std::string internalError = loadContentFile("/500InternalError.html");
        std::perror(("Server doesn't handle the extension of the file " + info.at("PATH")).c_str());
        setResponsContent(responsContent, info.at("PROTOCOL"), "500 Internal Server Error", contentType, internalError);
		return ;
    }
    if (contentFile.empty())
    {
        std::string notFound = loadContentFile("/404NotFound.html");
        setResponsContent(responsContent, info.at("PROTOCOL"), "404 Not Found", contentType, notFound);
        return ;
    }
    setResponsContent(responsContent, info.at("PROTOCOL"), "200 OK", contentType, contentFile);
    return ;
}