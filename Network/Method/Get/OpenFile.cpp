/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:55:10 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/29 14:04:59 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HeadersGet.hpp"
# include "../Utils.hpp"


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

void    openFile(MAP_STRING info, MAP_STRING &responsContent)
{
    std::string contentType = contentExtension(info.at("PATH"));
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