/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetFormValue.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:11:39 by theophilebr       #+#    #+#             */
/*   Updated: 2023/07/03 14:30:30 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeadersPost.hpp"
#include "../Utils.hpp"

void	createImgFile(std::string const &imgBody, std::string const &imgName, std::string const &extension,
						 MAP_STRING &responsContent, MAP_STRING &info)
{
	std::string body;
	std::string file = "Network/HtmlFiles/Image/" + imgName;
	std::string contentType = contentExtension(extension);
	std::ofstream ofs (file, std::ios_base::out | std::ios_base::binary);
	if (isInternalError(info, responsContent, contentType) < 0)
        return ;
	if (ofs.fail())
	{
		std::perror(("Failed to upload the file located at " + file).c_str());
        setResponsContent(responsContent, info.at("PROTOCOL"), "400 Bad Request", contentType, body);
		return ;
	}
	ofs << imgBody;
	ofs.close();
	setResponsContent(responsContent, info.at("PROTOCOL"), "204 No Content", contentType, body);
	return ;
}

void	getImgBody(std::string const &buffer, std::string const &imgName, std::string const &extension,
					 MAP_STRING &responsContent, MAP_STRING &info)
{
	std::string imgBody;
	std::string delimiter;

	for (int i = 0; buffer[i] != '\n' && buffer[i] != '\r'; i++)
		delimiter += buffer[i];
	delimiter += "--";
	int j = buffer.find("Content-Type:");
	while (buffer[j] != '\n' && buffer[j] != '\r')
		j++;
	while (buffer[j] == '\n' || buffer[j] == '\r')
		j++;
	int t = buffer.find(delimiter);
	while (j < t)
	{
		imgBody += buffer[j];
		j++;
	}
	createImgFile(imgBody, imgName, extension, responsContent, info);

}

void	getImg(std::string const &buffer, MAP_STRING &info, std::string toFind, MAP_STRING &responsContent)
{
	std::string	path;
	std::string imgName;
	std::string extension;
	
	for (int j = buffer.find(toFind.c_str(), 0, toFind.size()) + toFind.size() + 1; buffer[j] != '"'; j++)
	{
		if (buffer[j] == '"')
			j++;
		imgName += buffer[j];
	}
	std::cout << "\n image name : " << imgName << "\n\n";
	for (int i = imgName.find("."); imgName[i] && imgName[i] != '\r'; i++)
		extension += imgName[i];
	std::cout << "\n EXTENSIOn : " << extension << "\n\n";
	getImgBody(buffer, imgName, extension, responsContent, info);
}

void    getFormValue(std::string const &content, MAP_STRING &info, MAP_STRING &responsContent)
{
	getImg(content, info, "filename=", responsContent);
}