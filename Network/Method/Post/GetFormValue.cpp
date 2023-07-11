/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetFormValue.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:11:39 by theophilebr       #+#    #+#             */
/*   Updated: 2023/07/10 15:20:16 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeadersPost.hpp"

void	createFile(std::string const &fileBody, std::string const &fileName, std::string const &extension,
						 MAP_STRING &responsContent, MAP_STRING &info, std::string type,  ConfigParser::t_serv &servInfo)
{
	ConfigParser::t_route route = isRoute(info, responsContent, servInfo);
    if (route.a_route.empty())
    {
        std::cout << "empty \n\n";
            return ;
    }
	std::string contentType = contentExtension(extension);
	if (isInternalError(info, responsContent, contentType) < 0)
        return ;
	std::string body;
	if (type == "file")
	{
		std::string file = route.d_root.substr(1) + info.at("PATH").substr(1) + "/" + fileName;
		std::cout << "uplaoding file located at : " << route.d_root.substr(1) + info.at("PATH").substr(1) + "/" + fileName << "\n\n";
			std::ofstream ofs (file);
		if (ofs.fail())
		{
			std::perror(("Failed to upload the file located at " + file).c_str());
			setResponsContent(responsContent, info.at("PROTOCOL"), "400 Bad Request", contentType, body);
			return ;
		}
		ofs << fileBody;
		ofs.close();
	}
	if (type == "image")
	{
		std::cout << "uplaoding file located at : " << route.d_root.substr(1) + info.at("PATH").substr(1) + "/" + fileName << "\n\n";
		std::string file = route.d_root.substr(1) + info.at("PATH").substr(1) + "/" + fileName;
		std::ofstream ofs (file, std::ios_base::out | std::ios_base::binary);
		if (ofs.fail())
		{
			std::perror(("Failed to upload the file located at " + file).c_str());
			setResponsContent(responsContent, info.at("PROTOCOL"), "400 Bad Request", contentType, body);
			return ;
		}
		ofs << fileBody;
		ofs.close();

	}
	setResponsContent(responsContent, info.at("PROTOCOL"), "204 No Content", contentType, body);
	return ;
}

void	getFileBody(std::string const &buffer, std::string const &fileName, std::string const &extension,
					 MAP_STRING &responsContent, MAP_STRING &info,  ConfigParser::t_serv &servInfo)
{
	std::string fileBody;
	std::string delimiter;
	std::string type;

	for (int i = 0; buffer[i] != '\n' && buffer[i] != '\r'; i++)
		delimiter += buffer[i];
	delimiter += "--";
	int j = buffer.find("Content-Type:") + 14;
	while (buffer[j] != '\n' && buffer[j] != '\r')
	{
		type += buffer[j];
		j++;
	}
	if (type.find("text") != std::string::npos)
		type = "file";
	else if (type.find("image") != std::string::npos)
		type = "image";
	while (buffer[j] == '\n' || buffer[j] == '\r')
		j++;
	int t = buffer.find(delimiter);
	while (j < t)
	{
		fileBody += buffer[j];
		j++;
	}
	createFile(fileBody, fileName, extension, responsContent, info, type, servInfo);

}

void	getFile(std::string const &buffer, MAP_STRING &info, std::string toFind, MAP_STRING &responsContent,  ConfigParser::t_serv &servInfo)
{
	std::string	path;
	std::string fileName;
	std::string extension;
	
	for (int j = buffer.find(toFind.c_str(), 0, toFind.size()) + toFind.size() + 1; buffer[j] != '"'; j++)
	{
		if (buffer[j] == '"')
			j++;
		fileName += buffer[j];
	}
	std::cout << "\n file name : " << fileName << "\n\n";
	for (int i = fileName.find("."); fileName[i] && fileName[i] != '\r'; i++)
		extension += fileName[i];
	std::cout << "\n EXTENSIOn : " << extension << "\n\n";
	getFileBody(buffer, fileName, extension, responsContent, info, servInfo);
}

void    getFormValue(std::string const &content, MAP_STRING &info, MAP_STRING &responsContent,  ConfigParser::t_serv &servInfo)
{
	getFile(content, info, "filename=", responsContent, servInfo);
}