/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetResponsContent.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:24:56 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/03/10 13:23:36 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GetResponsContent.hpp"

RESPONS::GetResponsContent::GetResponsContent(MAP_STRING &info, std::string const &file) : _info(info)
{	
	setContentType(info, file);
	if (_contentType.empty())
	{
		_contentType = "Content-Type not supported\r\n";
		return ;
	}
	//std::cout << "content type : " << _contentType << "\n";
	_content = loadContentFile(file, info);
	std::string size = ft_itoa(_content.size());
	_contentLength = "Content-Length : " + size + "\r\n";
    return ;
}

RESPONS::GetResponsContent::~GetResponsContent(void)
{
    return ;
}

// void	getUserValue(std::string &tmp, MAP_STRING const &info)
// {
// 	std::string imagePath = "Image/" + info.at("SPORT") + ".svg";
// 	//std::cout << "\nReplace Username Image path : " << imagePath << "\n\n";
// 	try	{
// 		tmp.replace(tmp.find("UserName"), 8, info.at("FIRSTNAME"));
// 		tmp.replace(tmp.find("UserSport"), 9, imagePath);
// 		tmp.replace(tmp.find("ProfilPic"), 9, info.at("PROFILPIC"));
// 	}
// 	catch (const std::out_of_range& oor) 
// 	{
		
//   	}
// 	return ;
// }

std::string	RESPONS::GetResponsContent::loadContentFile(std::string contentFile, MAP_STRING const &info)
{	
	//std::cout << "\nhtml file : " << contentFile << "\n\n";
	std::string file = "Network/HtmlFiles" + contentFile;
	std::string	tmp;
	std::ifstream ifs (file.c_str(), std::ifstream::in);
	if(ifs.fail())
	{
		std::cout << "\nopen file failed \n\n";
		return (tmp);
	}
	char	c = ifs.get();
	while (ifs.good())
	{
		tmp += c;
		c = ifs.get(); 
	}
	ifs.close();
	// if (contentFile == "/Profil.html")
	// 	getUserValue(tmp, info);
	//std::cout << "end of load contentfile with tmp : " << tmp << "\n";
	return (tmp);
}

std::string	RESPONS::GetResponsContent::getContent(void) const
{
	return (_content);
}

std::string RESPONS::GetResponsContent::getContentType(void) const
{
	return (_contentType);
}

std::string RESPONS::GetResponsContent::getContentLength(void) const
{
	return (_contentLength);
}

void		RESPONS::GetResponsContent::setExtension(void)
{
	_extension.insert(std::pair<std::string, std::string>(".html", "Content-Type: text/html\r\n"));
	_extension.insert(std::pair<std::string, std::string>(".css", "Content-Type: text/css\r\n"));
	_extension.insert(std::pair<std::string, std::string>(".svg", "Content-Type: image/svg+xml\r\n"));
	_extension.insert(std::pair<std::string, std::string>(".png", "Content-Type: image/png\r\n"));
	return ;
}

// void		RESPONS::GetResponsContent::setSportImage(void)
// {
// 		_extension.insert(std::pair<std::string, std::string>("Basket", "Image/Basket.svg"));
// 		_extension.insert(std::pair<std::string, std::string>("Jogging", "Image/Course.svg"));
// 		_extension.insert(std::pair<std::string, std::string>("Football", "Image/Football.svg"));
// 		_extension.insert(std::pair<std::string, std::string>("Ski", "Image/Ski.svg"));

// 	return ;
// }

void		RESPONS::GetResponsContent::setContentType(MAP_STRING const &info, std::string const &file)
{
	std::string extension;
	
	setExtension();
	for (int i = file.find("."); file[i]; i++)
		extension += file[i];
	//std::cout << "extension : " << extension << "\n";
	try 
	{
		_contentType = _extension.at(extension);
	}
	catch (const std::out_of_range &e)
	{
	}
	
	//std::cout << "_contentTupe : " << _contentType << "\n";
}
