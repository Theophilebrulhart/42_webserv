/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetFormValue.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:11:39 by theophilebr       #+#    #+#             */
/*   Updated: 2023/06/27 16:02:40 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeadersRequestInfo.hpp"

void	createImgFile(std::string const &imgBody, std::string const &imgName, std::string const &extension)
{
	std::string file = "Network/HtmlFiles/Image/" + imgName;
	std::ofstream ofs (file, std::ios_base::out | std::ios_base::binary);
	if (ofs.fail())
	{
		std::cout << "Sorry, we can't build your file\n";
		return ;
	}
	ofs << imgBody;
	ofs.close();
	return ;
}

void	getImageBody(std::string const &buffer, std::string const &imgName, std::string const &extension)
{
	//std::vector<unsigned char> imgBodyV;
	std::string imgBody;
	std::string delimiter;

	for (int i = 0; buffer[i] != '\n' && buffer[i] != '\r'; i++)
		delimiter += buffer[i];
	delimiter += "--";
	// std::cout << "\ndelimiter : " << delimiter << "\n";
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
	//std::cout << "\n+++++++++++++++++++++++++++++++++++++++++test" << imgBody.substr(0, 1000) << "\n";
	createImgFile(imgBody, imgName, extension);

}

void	getProfilPic(std::string const &buffer, MAP_STRING &info, std::string toFind, std::string name)
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
	getImageBody(buffer, imgName, extension);
}

void    getFormValue(std::string const &content, MAP_STRING &info)
{
	getProfilPic(content, info, "filename=", "PROFILPIC");
}