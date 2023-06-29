/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:48:40 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/29 15:21:39 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

std::string ft_itoa(int n)
{
    std::ostringstream oss;
    oss << n;
    return oss.str();
}

std::string contentExtension(std::string const &file)
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

void setResponsContent(MAP_STRING& responsContent, std::string protocol, std::string status,
                       std::string contentType, std::string body)
{
    if (!protocol.empty())
        responsContent.insert(std::make_pair("Aprotocol", protocol));
    if (!status.empty())
        responsContent.insert(std::make_pair("Bstatus", status));
    if (!contentType.empty())
        responsContent.insert(std::make_pair("CcontentType", contentType));
    if (!body.empty())
    {
        responsContent.insert(std::make_pair("DcontentLength", std::string("Content-Length: ") + ft_itoa(body.size())));
        responsContent.insert(std::make_pair("Ebody", body));
    }
    return ;
}

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
