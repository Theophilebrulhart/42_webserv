/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:48:40 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/17 14:06:34 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeadersMethod.hpp"

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
	extension.insert(std::pair<std::string, std::string>(".js", "Content-Type: application/javascript"));
	extension.insert(std::pair<std::string, std::string>(".php", "Content-Type: text/php"));

	
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

std::string loadContentFile(std::string contentFile, std::string root)
{	
	std::string file = root + contentFile;
	// std::cout << "\nContentFile in loadcontent: " << file << "\n\n";
	std::string	tmp;
	std::ifstream ifs (file.c_str(), std::ifstream::in);
	if(ifs.fail())
	{
		std::perror(("Failed to open the file located at " + file).c_str());
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

int isValidMethod(const MAP_STRING& info)
{
    MAP_STRING validMethods;

    validMethods.insert(std::make_pair("getMethod", "GET"));
    validMethods.insert(std::make_pair("postMethod", "POST"));
    validMethods.insert(std::make_pair("deleteMethod", "DELETE"));

    MAP_STRING::const_iterator it = validMethods.begin();
    for (; it != validMethods.end(); ++it)
    {
        if (info.find("METHOD") != info.end() && info.at("METHOD") == it->second)
            return (1);
    }
    return (-1);
}

bool isFile(const std::string& path)
{
	// std::cout << "isfile file :" <<  path << "\n\n";
    struct stat fileStat;
    if (stat(path.c_str(), &fileStat) != 0)
    {
        // Erreur lors de la récupération des informations du fichier
        return false;
    }
    return S_ISREG(fileStat.st_mode);
}

bool isDir(const std::string& path)
{

	// std::cout << "isDir path :" <<  path << "\n\n";

    struct stat fileStat;
	
    if (stat(path.c_str(), &fileStat) != 0)
    {
        // Erreur lors de la récupération des informations du fichier
        return false;
    }
    return S_ISDIR(fileStat.st_mode);
}

int	exist (MAP_STRING &responsContent, ConfigParser::t_route route, MAP_STRING &info, ConfigParser::t_serv &servInfo)
{
	if (info.at("METHOD") != "DELETE")
	{
		if (!isFile(route.d_root.substr(1) + info.at("PATH").substr(1)) && !isDir(route.d_root.substr(1) + info.at("PATH").substr(1)))
		{
			std::cout << "Not a existing file or directory : " << route.d_root.substr(1) + info.at("PATH").substr(1) << " \n\n";
			notFound(responsContent, servInfo);
			return (0);
		}
	}
	return (1);
}

int    isMethodAllowed(std::string method, MAP_STRING &responsContent, ConfigParser::t_route route, MAP_STRING &info, ConfigParser::t_serv servInfo)
{
	std::string file;
	std::vector<std::string>::iterator it = std::find(route.b_methods.begin(), route.b_methods.end(), method);
	if (it != route.b_methods.end()) {
		return (1);
    } else {
		forbiddenMethod(responsContent, servInfo);
		return (0);
    }
	return (1);
}

std::string    findSlash(const std::string &url)
{
    std::string str    = url.substr(1);
    size_t	start = str.find_first_of('/');
    if (start == std::string::npos)
    {
        std::string    r = "/" + str;
        return r;
    }
    else
    {
        std::string r = str.substr(0, start);
        r = '/' + r;
        return r;
    }
}

ConfigParser::t_route isRoute(MAP_STRING &info, MAP_STRING &responsContent, ConfigParser::t_serv &servInfo)
{
	// std::cout << "is route ? the serv route is : " << servInfo.a_route << "\n\n";
	ConfigParser::t_route empty;
	std::string path = info.at("PATH");
	std::cout << "The path :" << path << std::endl;
	if (path.size() == 1)
	{
		// std::cout << "route sze 1\n\n";
		if (servInfo.c_routes.find(path) != servInfo.c_routes.end() && path != "/")
		{
			// std::cout << "route : " << info.at("PATH") << "\n\n";
			forbidden(responsContent, servInfo);
			return (empty);
		}
		// std::cout << "path = " << path << std::endl;
		if (!isMethodAllowed(info.at("METHOD"), responsContent, servInfo.c_routes[path], info, servInfo))
			return (empty);
		// std::cout << "return size 1 route : " << servInfo.c_routes[path].a_route << "\n\n";
		return (servInfo.c_routes[path]);
	}
	std::string route = findSlash(path);
	// std::cout << "route eee: " << route << "\n\n";
	if (servInfo.c_routes.find(route) == servInfo.c_routes.end())
	{
		std::cout << "\nRoute non trouvee\n\n";
		if (!exist(responsContent, servInfo.c_routes["/"], info, servInfo))
			return (empty);
		if (!isMethodAllowed(info.at("METHOD"), responsContent, servInfo.c_routes["/"], info, servInfo))
			return (empty);
		return (servInfo.c_routes["/"]);
	}
	// std::cout << "Route trouvee : " << servInfo.c_routes[route].a_route << "\n\n";
	if (!servInfo.c_routes[route].c_redirec.empty())
	{
		 std::cout << "no / at the end of this directory\n\n";
		redirection(responsContent, "Location: " + servInfo.c_routes[route].c_redirec.substr(1));
		return (empty);
	}
	if (!isMethodAllowed(info.at("METHOD"), responsContent, servInfo.c_routes[route], info, servInfo))
		return (empty);
	return (servInfo.c_routes[route]);
}

