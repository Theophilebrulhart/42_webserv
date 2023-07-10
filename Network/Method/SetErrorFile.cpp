/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetErrorFile.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:24:01 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/10 16:48:40 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HeadersMethod.hpp"

std::string loadContentFile(std::string contentFile)
{	
	std::cout << "\nContentFile : " << contentFile << "\n\n";
	std::string file = "Network/Website/HtmlFiles/ErrorFiles" + contentFile;
	std::string	tmp;
	std::ifstream ifs (file.c_str(), std::ifstream::in);
	if(ifs.fail())
	{
		std::perror(("Failed to open the file located at " + contentFile).c_str());
		return (tmp);
	}
	char	c = ifs.get();
	while (ifs.good())
	{
		tmp += c;
		c = ifs.get(); 
	}
	ifs.close();

	return (tmp);
}

void setInternalError(std::string handle, std::string problem, MAP_STRING &responsContent, std::string protocol,
						std::string contentType)
{
	std::string internalError = loadContentFile("/500InternalError.html");
	std::perror(("Server doesn't handle the " + handle + problem).c_str());
	setResponsContent(responsContent, protocol, "500 Internal Server Error", contentType, internalError);
	return ;
}

int isInternalError( MAP_STRING &info, MAP_STRING &responsContent, std::string contentType)
{
	if (isValidMethod(info) < 0)
    {
    	setInternalError("METHOD :", info.at("METHOD"), responsContent, info.at("PROTOCOL"), contentType);
		return (-1);
    }
	if (contentType == "Not supported")
    {
        setInternalError("extension of the file :", info.at("PATH"), responsContent, info.at("PROTOCOL"), contentType);
	    return (-1);
    }
	return (1);
}

void notFound(MAP_STRING &responsContent)
{
	std::string notFound = loadContentFile("/404NotFound.html");
	setResponsContent(responsContent, "HTTP/1.1", "404 Not Found", "text/html", notFound);
	return ;
}

void forbiddenMethod(MAP_STRING &responsContent)
{
	std::string forbidden = loadContentFile("/405Forbidden.html");
	setResponsContent(responsContent, "HTTP/1.1", "405 Method Not Allowed", "text/html", forbidden);
	return ;
}

void forbidden(MAP_STRING &responsContent)
{
	std::string forbidden = loadContentFile("/403Forbidden.html");
	setResponsContent(responsContent, "HTTP/1.1", "403 Forbidden", "text/html", forbidden);
	return ;
}

void redirection(MAP_STRING &responsContent, std::string newUrl)
{
	std::string body;
	setResponsContent(responsContent, "HTTP/1.1", "302 Found", newUrl, body);
	return ;
}