/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:44:14 by pyammoun          #+#    #+#             */
/*   Updated: 2023/07/04 13:42:30 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"


CGI::CGI() {

}

CGI::CGI(const MAP_STRING &_requestInfo, const MAP_STRING &_responsContent) {
	setUpEnv(_requestInfo, _responsContent);
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
	//The real path of the script being executed.
	_env["SCRIPT_FILENAME"] = "";
	//value after the ?
	try {
	_env["QUERY_STRING"] = _requestInfo.at("RAWCONTENT"); 
	}
	catch (const std::exception& ex) {
       	_env["QUERY_STRING"] = ""; 
    }
	_env["REQUEST_URI"] = _requestInfo.at("PATH");
	//CGIFiles/hw.php/cactus -> cactus
	_env["PATH_INFO"] = extractPathInfo(_requestInfo.at("PATH")); 
	_env["PATH_TRANSLATED"] = CGI_FILEPATH + _env["SCRIPT_NAME"];
	}
	catch (const std::exception& ex) {
        std::cerr << "Exception caught owow: " << ex.what() << std::endl;
    }
	PrintMap(_env);	
	std::cout << Exec() << std::endl;
}


std::string		CGI::Exec(void) {
	pid_t		pid;
	int			saveStdin;
	int			saveStdout;
	char		**env;
	std::string	newBody;

	try {
		env = getEnvAsCstrArray();
	}
	catch (std::bad_alloc &e) {
		std::cerr << e.what() << std::endl;
	}

	// SAVING STDIN AND STDOUT IN ORDER TO TURN THEM BACK TO NORMAL LATER
	saveStdin = dup(STDIN_FILENO);
	saveStdout = dup(STDOUT_FILENO);

	FILE	*fIn = tmpfile();
	FILE	*fOut = tmpfile();
	long	fdIn = fileno(fIn);
	long	fdOut = fileno(fOut);
	int		ret = 1;

	write(fdIn, _body.c_str(), _body.size());
	lseek(fdIn, 0, SEEK_SET);

	pid = fork();

	if (pid == -1)
	{
		std::cerr <<  "Fork crashed." << std::endl;
		return ("Status: 500\r\n\r\n");
	}
	else if (!pid)
	{
		char * const * nll = NULL;

		dup2(fdIn, STDIN_FILENO);
		dup2(fdOut, STDOUT_FILENO);
		execve(_env["PATH_TRANSLATED"].c_str(), nll, env);
		std::cerr << "Execve crashed." << std::endl;
		write(STDOUT_FILENO, "Status: 500\r\n\r\n", 15);
	}
	else
	{
		char	buffer[CGI_BUFSIZE] = {0};

		waitpid(-1, NULL, 0);
		lseek(fdOut, 0, SEEK_SET);

		ret = 1;
		while (ret > 0)
		{
			memset(buffer, 0, CGI_BUFSIZE);
			ret = read(fdOut, buffer, CGI_BUFSIZE - 1);
			newBody += buffer;
		}
	}

	dup2(saveStdin, STDIN_FILENO);
	dup2(saveStdout, STDOUT_FILENO);
	fclose(fIn);
	fclose(fOut);
	close(fdIn);
	close(fdOut);
	close(saveStdin);
	close(saveStdout);

	try {
		for (size_t i = 0; env[i]; i++)
			delete[] env[i];
		delete[] env;
	}
	catch (const std::exception& ex) {
        std::cerr << "Exception caught: " << ex.what() << std::endl;
    }	

	if (!pid)
		exit(0);

	return (newBody);
}

char		**CGI::getEnvAsCstrArray(void) const {
	int	s = _env.size();
	char	**env = new char*[s];
	int	j = 0;
	for (std::map<std::string, std::string>::const_iterator i = this->_env.begin(); i != this->_env.end(); i++) {
		std::string	element = i->first + "=" + i->second;
		env[j] = new char[element.size() + 1];
		env[j] = strcpy(env[j], (const char*)element.c_str());
		j++;
	}
	env[j] = NULL;
	// printStringArray(env);
	return env;
}

std::string	CGI::extractScriptName(const std::string &url)
{
	std::size_t	start = url.find("/path/");
	if (start == std::string::npos)
		return ("");
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
	if (start + 5 == std::string::npos)
		return ("");
	std::size_t end = url.find("?");
	if (end == std::string::npos)
	{
		end = url.size();
		std::string str = url.substr(start + 5, end - 1);
	}
	if (start + 5 != end)
	{
		std::string str = url.substr(start + 5, end - 1);
		return (str);
	}
	return ("");		

}

std::string	CGI::extractQueryString(const std::string &url) {
	std::size_t	start = url.find('?');
	if (start != std::string::npos)
		return (url.substr(start));
	return  ("");
}