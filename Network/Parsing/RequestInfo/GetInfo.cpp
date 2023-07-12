/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetInfo.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophilebrulhart <theophilebrulhart@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:34:27 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/12 10:16:11 by theophilebr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HeadersRequestInfo.hpp"
# include <cstring>

void getMethod(std::string& buffer, std::map<std::string, std::string>& info)
{
   std::string method;
    size_t methodEndPos = buffer.find(' ');

    if (methodEndPos != std::string::npos)
    {
        method = buffer.substr(0, methodEndPos);
        for (size_t i = 0; i < method.length(); ++i)
        {
            method[i] = std::toupper(method[i]);
        }
    }
	info["METHOD"] = method;
}

void	getPath(std::string &buffer, MAP_STRING &info, std::string toFind, std::string name)
{
	std::string	path;
	std::string	rawContent;
	std::string	extension;
	std::string tmpPath;
	
	for (int i = buffer.find(toFind.c_str(), 0, toFind.size()); buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\r'; i++)
	{
		path += buffer[i];
	}
	if (path.find("?") != std::string::npos)
	{
		
		int	j = path.find("?");
		for (int t = 0; t < j; t++)
			tmpPath += path[t];
		while (path[++j])
			rawContent += path[j];
		if (!rawContent.empty())
		{
			try 
			{
    			info.at("RAWCONTENT") = rawContent;
			}
			catch (const std::out_of_range& oor) 
			{
				info.insert(std::pair<std::string, std::string>("RAWCONTENT", rawContent));
			}
		}
	}
	else
		tmpPath = path;
	if (name == "PATH" && path.rfind(".") != std::string::npos)
	{
		for (int i = path.rfind("."); path[i] && path[i] != '?' && path[i] != '/'; i++)
			extension += path[i];
		try 
		{
			info.at("EXTENSION") = extension;
		}
		catch (const std::out_of_range& oor) 
		{
			info.insert(std::pair<std::string, std::string>("EXTENSION", extension));
		}
	}
	try 
	{
    	info.at(name) = tmpPath;
  	}
  	catch (const std::out_of_range& oor) 
	{
		info.insert(std::pair<std::string, std::string>(name, tmpPath));
  	}
	
	return ;
}

void	getSection(std::string &buffer, MAP_STRING &info, std::string toFind, std::string name)
{
	std::string path;
	
	if (buffer.find(toFind.c_str(), 0, toFind.size()) != std::string::npos)
	{
		int i = buffer.find(toFind.c_str(), 0, toFind.size());
		
		while (buffer[i] != ' ')
			i++;
		i++;
		while (buffer[i] && buffer[i] != '\n')
		{
			path += buffer[i];
			i++;
		}
		if (name == "TYPE")
		{
			if (path.find("text") != std::string::npos)
				path = "text";
			if (path.find("image") != std::string::npos)
				path = "image";
		}
		try 
		{
			info.at(name) = path;
		}
		catch (const std::out_of_range& oor) 
		{
			info.insert(std::pair<std::string, std::string>(name, path));
		}
	}
	
}

std::string getLastLine(std::string& buffer) {
    std::string::size_type pos = buffer.find_last_of('\n');
    if (pos != std::string::npos) {
        // Skip the newline character if it is the last character
        if (pos > 0 && buffer[pos - 1] == '\r') {
            --pos;
        }
		pos++;
        return buffer.substr(pos + 1);
    }
    return buffer;
}

void	getInfo(std::string &buffer, MAP_STRING &info)
{
	getMethod(buffer, info);
    getPath(buffer, info, "/", "PATH");
    info.insert(std::pair<std::string, std::string>("PROTOCOL", "HTTP/1.1"));
	getSection(buffer, info, "Host:", "HOST");
	getSection(buffer, info, "Connection:", "CONNECTION");
	getSection(buffer, info, "Accept", "TYPE");
	getSection(buffer, info, "Expect", "EXPECT");
	getSection(buffer, info, "Content-Type", "CONTENT-TYPE");
	getSection(buffer, info, "Content-Length", "CONTENT-LENGTH");
	try {
	if (info["CONTENT-TYPE"] == "application/x-www-form-urlencoded\r")
		info["CGIBODY"] = getLastLine(buffer);	
	}
	catch (const std::out_of_range& oor) 
	{
		info["CONTENT_TYPE"] = "";
	}
}