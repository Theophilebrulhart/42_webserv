/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:55:10 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/28 17:40:37 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HeadersGet.hpp"


std::string loadContentFile(std::string contentFile)
{	
	std::string file = "Network/HtmlFiles" + contentFile;
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

std::string contentExtension(MAP_STRING const &info, std::string const &file)
{
	MAP_STRING extension;
    std::string tmp;
    std::string contentType;

    extension.insert(std::pair<std::string, std::string>(".html", "Content-Type: text/html"));
	extension.insert(std::pair<std::string, std::string>(".css", "Content-Type: text/css"));
	extension.insert(std::pair<std::string, std::string>(".svg", "Content-Type: image/svg+xml"));
	extension.insert(std::pair<std::string, std::string>(".png", "Content-Type: image/png"));
	extension.insert(std::pair<std::string, std::string>(".jpeg", "Content-Type: image/jpeg"));
	
	for (int i = file.find("."); file[i]; i++)
		tmp += file[i];
	//std::cout << "extension : " << extension << "\n";
	try 
	{
		contentType = extension.at(tmp);
	}
	catch (const std::out_of_range &e)
	{
        contentType = "Not supported";
	}
	return (contentType);
}

void setResponsContent(MAP_STRING &responsContent, std::string protocol, std::string status, std::string contentType, std::string body)
{
    responsContent.insert(std::pair<std::string, std::string>("protocol", protocol));
    responsContent.insert(std::pair<std::string, std::string>("status", status));
    responsContent.insert(std::pair<std::string, std::string>("contentType", contentType));
    responsContent.insert(std::pair<std::string, std::string>("body", body));
}

void    openFile(MAP_STRING info, MAP_STRING &responsContent)
{
    std::string contentType = contentExtension(info, info.at("PATH"));
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