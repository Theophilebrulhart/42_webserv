/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteFile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:25:27 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/29 15:29:33 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HeadersDelete.hpp"
# include "../Utils.hpp"

void deleteFile(MAP_STRING &info, MAP_STRING &responsContent)
{
    std::string body;
    std::string fileToDelete = "Network/HtmlFiles/Image/" + info.at("PATH");
    std::string contentType = contentExtension(info.at("PATH"));
    if (contentType == "Not supported")
    {
        std::string internalError = loadContentFile("/500InternalError.html");
        std::perror(("Server doesn't handle the extension of the file " + fileToDelete).c_str());
        setResponsContent(responsContent, info.at("PROTOCOL"), "500 Internal Server Error", contentType, internalError);
		return ;
    }
    if (std::remove(fileToDelete.c_str()) != 0)
    {
        std::perror(("Failed to delete the file located at " + fileToDelete).c_str());
        setResponsContent(responsContent, info.at("PROTOCOL"), "400 Not Found", contentType, body);
		return ;
    }
   setResponsContent(responsContent, info.at("PROTOCOL"), "204 No Content", contentType, body);
   return ;
}