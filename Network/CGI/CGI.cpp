/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:44:14 by pyammoun          #+#    #+#             */
/*   Updated: 2023/07/03 15:52:14 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"


CGI::CGI() {

}

CGI::CGI(const MAP_STRING &_requestInfo, const MAP_STRING &_responsContent) {
	setUpEnv(_requestInfo, _responsContent);
	std::cout << "la" << std::endl;
}

CGI::~CGI(void) {

}

void	CGI::setUpEnv(const MAP_STRING &_requestInfo, const MAP_STRING &_responsContent)
{
	std::map<std::string, std::string>::iterator	it;

	try {
	_env["REDIRECT_STATUT"] = "200";
	_env["GATEWAY_INTERFARCE"] = "CGI/1.1";
	_env["REQUEST_METHOD"] = _requestInfo.at("METHOD");
	_env["AUTH_TYPE"] = "";
	_env["CONTENT_TYPE"] = _requestInfo.at("TYPE");
	std::string	len =  _responsContent.at("DcontentLength"); 
	_env["CONTENT_LENGTH"] = len.erase(0, 16);
	_env["SERVER_PORT"] = "80";
	_env["SERVER_PROTOCOL"] = _requestInfo.at("PROTOCOL");
	_env["SCRIPT_NAME"] = extractScriptName(_requestInfo.at("PATH"));
	_env["SCRIPT_FILENAME"] = ""; 
	_env["QUERY_STRING"] = _requestInfo.at("RAWCONTENT"); 
	_env["REQUEST_URI"] = _requestInfo.at("PATH");
	_env["PATH_INFO"] = extractPathInfo(_requestInfo.at("PATH")); 
	}
	catch (const std::exception& ex) {
        std::cerr << "Exception caught: " << ex.what() << std::endl;
    }

	
	
	PrintMap(_env);	
}

std::string	CGI::extractScriptName(const std::string &url)
{
	std::size_t	start = url.find("/path/");
	std::size_t end = url.find(".php");
	if (end == std::string::npos)
		return ("");
	std::string str = url.substr(start + 5, std::string::npos);
	str.resize(end - start - 1);
	return (str);
}

std::string	CGI::extractPathInfo(const std::string &url)
{
	std::size_t	start = url.find(".php");
	std::size_t end = url.find("?");
	if (end == std::string::npos)
		std::cout << "caca" << std::endl;
	
	std::string str = url.substr(start + 5, end - 1);
	return (str);
}

std::string	CGI::extractQueryString(const std::string &url) {
	std::size_t	start = url.find('?');
	if (start != std::string::npos)
		return (url.substr(start));
	return  ("");
}