/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:44:14 by pyammoun          #+#    #+#             */
/*   Updated: 2023/07/07 13:38:26 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"


CGI::CGI() {

}

CGI::CGI(const MAP_STRING &_requestInfo,  MAP_STRING &_responsContent) {
	setUpEnv(_requestInfo, _responsContent);
}

CGI::~CGI(void) {

}

void	CGI::setUpEnv(const MAP_STRING &_requestInfo, MAP_STRING &_responsContent)
{
	std::map<std::string, std::string>::iterator	it;

	// try {
	
	_env["REQUEST_METHOD"] = _requestInfo.at("METHOD");
	_env["AUTH_TYPE"] = "";
	if (_env["REQUEST_METHOD"] == "GET")
	{
		_env["CONTENT_TYPE"] = ""; 
		_env["CONTENT_LENGTH"] = "";
	}
	// _env["CONTENT_TYPE"] = _requestInfo.at("TYPE");
	// std::string	len =  _responsContent.at("DcontentLength"); 
	// _env["CONTENT_LENGTH"] = len.erase(0, 16);
	// _env["SERVER_NAME"] = "Mahmud";
	// _env["SERVER_PORT"] = "80";
	// _env["SERVER_PROTOCOL"] = _requestInfo.at("PROTOCOL");
	// _env["SERVER_SOFTWARE"] = "WEBSERV/1.0"; 
	// _env["SCRIPT_NAME"] = "hw.php";
	// // extractScriptName(_requestInfo.at("PATH"));
	// //The real path of the script being executed.
	// _env["SCRIPT_FILENAME"] = "/Users/pyammoun/Documents/webserve/Network/CGIFiles/hw.php";
	// //  CGI_FILEPATH + _env["SCRIPT_NAME"];
	//  _env["DOCUMENT_ROOT"] = "";
	// //value after the ?
	
	// error at compilation
	// _env["REQUEST_URI"] = _requestInfo.at("PATH");
	// //CGIFiles/hw.php/cactus -> cactus

	// }
	// catch (const std::exception& ex) {
    //      std::cerr << "Exception caught owow: " << ex.what() << std::endl;
    // }
	// PrintMap(_env);	
	_env["GATEWAY_INTERFACE"]="CGI/1.1";
	_env["SERVER_PROTOCOL"]="HTTP/1.1";
	//name of the script being executed	
	_env["SCRIPT_NAME"]= extractScriptName(_requestInfo.at("PATH"));
	//The real path of the script being executed.
	_env["SCRIPT_FILENAME"]= CGI_FILEPATH + _env["SCRIPT_NAME"];
	_env["REDIRECT_STATUS"]="200";	
	_env["PATH_INFO"] = extractPathInfo(_requestInfo.at("PATH")); 
	if (_env["PATH_INFO"] != "")
		_env["PATH_TRANSLATED"] = CGI_FILEPATH + _env["SCRIPT_NAME"] + '/' + _env["PATH_INFO"];
	else
		_env["PATH_TRANSLATED"] = ""; 
	try {
	_env["QUERY_STRING"] = _requestInfo.at("RAWCONTENT"); 
	}
	catch (const std::exception& ex) {
       	_env["QUERY_STRING"] = ""; 
    }
	Exec(_responsContent);
}

int		CGI::SetResponseContent(MAP_STRING &_responsContent, std::string output)
{
	size_t	f = output.find("\n");
	std::string	rep = output.substr(f + 1, output.size());
	f = rep.find("\n");
	output = rep.substr(f + 1, output.size());
	f = output.find("\n");
	rep = output.substr(f + 1, output.size());
	setResponsContent(_responsContent, "HTTP/1.1", "200 OK", "text/html", rep);
	return (1);	
}


int			CGI::Exec(MAP_STRING &_responsContent) {	
	char		**env;
	std::string	output;

	try {
		env = getEnvAsCstrArray();
	}
	catch (std::bad_alloc &e) {
		std::cerr << e.what() << std::endl;
	}
	//printStringArray(env);
	


	std::string s1 = CGI_PHP;
	std::string s2 = "./Netwrok/CGIFiles/hw.php";
	// std::cout << "s1 : " << s1 << std::endl;
	// std::cout << "s2 : " << s2 << std::endl;
	char* charS1 = new char[s1.length() + 1];
	std::strcpy(charS1, s1.c_str());
	char* charS2 = new char[s2.length() + 1];
	std::strcpy(charS2, s2.c_str());
	char* argv[] = {charS1, charS2, NULL};	

	int pipefd[2];
    if (pipe(pipefd) == -1) {
        std::cerr << "Error creating pipe" << std::endl;
        return 1;
    }

    int pid = fork();
    if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close the read end of the pipe

        // Redirect standard output to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execve(argv[0], argv, env);
        std::cerr << "Error executing PHP script" << std::endl;
        return 1;
    } 
	else if (pid > 0) {
        // Parent process
        close(pipefd[1]); // Close the write end of the pipe

        // Read the output from the read end of the pipe
        char buffer[10000];
        ssize_t bytesRead;
        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            output.append(buffer, bytesRead);
        }
        close(pipefd[0]);

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            std::cout << "Output of PHP script:" << std::endl;
            std::cout << output << std::endl;
        } else {
            std::cerr << "PHP script execution failed" << std::endl;
			//notfound
        }
    } else {
        // Fork failed
        std::cerr << "Error forking process" << std::endl;
        return 1;
    }
	SetResponseContent(_responsContent, output);
	return (0);

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
	std::size_t end = url.find(".php");
	if (end == std::string::npos)
		return ("");
	std::string	resize = url.substr(0, end + 4);
	std::size_t	sl = resize.find_last_of('/');	
	std::string file = resize.substr(sl + 1, resize.size());
	return (file);
}

std::string	CGI::extractPathInfo(const std::string &url)
{
	std::size_t	start = url.find(".php");	
	//case the url end with the .php
	if (start + 4 == (url.size()))
		return ("");
	std::size_t end = url.find("?");
	// case: there is no ? but there is a pathinfo
	if (end == std::string::npos)
	{
		end = url.size();
		std::string str = url.substr(start + 5, end);
		return (str);
	}
	// case: there is a ? but no path_info
	if (end == start + 5) 
		return ("");
	// case: there is a ? and there is a path info
	if (start + 5 != end)
	{
		std::string str = url.substr(start + 5, end);
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