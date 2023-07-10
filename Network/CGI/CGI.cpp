/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:44:14 by pyammoun          #+#    #+#             */
/*   Updated: 2023/07/10 20:08:45 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"


CGI::CGI() {

}

CGI::CGI(MAP_STRING &_requestInfo,  MAP_STRING &_responsContent) {
	setUpEnv(_requestInfo, _responsContent);
}

CGI::~CGI(void) {

}

void	CGI::setUpEnv(MAP_STRING &_requestInfo, MAP_STRING &_responsContent)
{
	std::map<std::string, std::string>::iterator	it;

	_env["REQUEST_METHOD"] = _requestInfo.at("METHOD");
	_env["AUTH_TYPE"] = "";
	if (_env["REQUEST_METHOD"] == "GET")
	{
		_env["CONTENT_TYPE"] = ""; 
		_env["CONTENT_LENGTH"] = "";
	}
	else
	{
		_env["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
		std::size_t		len = _requestInfo.at("CGIBODY").size();
		_env["CONTENT_LENGTH"] =  std::to_string(len);
		_env["CGIBODY"] = _requestInfo.at("CGIBODY");
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
	//BIG execution with the env variable 
	Exec(_responsContent);
	//Error handling in case smthing happend in the pipe 
	if (_ewor == 5 || _ewor == 4)
	{
		std:: string Error;
		if (_ewor == 5)
		{
			Error = "Error 500: Internal error";
			isInternalError(_requestInfo, _responsContent, "text/html");
		}
		else if (_ewor == 4)
		{
			Error = "Error 404: Not found";
			notFound(_responsContent);
		}
	}
}

int		CGI::SetResponseContent(MAP_STRING &_responsContent, std::string output)
{
	// if (_ewor == 5 || _ewor == 4)
	// {
	// 	if (_ewor == 5)
	// 	{
	// 		setResponsContent(_responsContent, "HTTP/1.1", "500 Internal error", "text/html", output);
	// 		return 0;
	// 	}
	// 	else if (_ewor == 4)
	// 	{
	// 		setResponsContent(_responsContent, "HTTP/1.1", "404 Not found", "text/html", output);
	// 		return 0;
	// 	}
	// }
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
	std::string s2 = _env["SCRIPT_FILENAME"];
	// std::cout << "s1 : " << s1 << std::endl;
	// std::cout << "s2 : " << s2 << std::endl;
	char* charS1 = new char[s1.length() + 1];
	std::strcpy(charS1, s1.c_str());
	char* charS2 = new char[s2.length() + 1];
	std::strcpy(charS2, s2.c_str());
	char* argv[] = {charS1, charS2, NULL};	

	pid_t	pid;
	int		pipe1[2];
	int		pipe2[2];
	
	//send data from parent to child
	if (pipe(pipe1) < 0)
	{
		std::cerr << "Error creating pipe" << std::endl;
		_ewor = 5;
		return 0;
	}
	//send data from child to parent
	if (pipe(pipe2) < 0)
	{
		std::cerr << "Error creating pipe" << std::endl;
		_ewor = 5;
		return 0;
	}
	pid = fork();
  
    if (pid == 0) {
        // Child process
        // Redirect standard output to the write end of the pipe
		dup2(pipe1[0], STDIN_FILENO);
		dup2(pipe2[1], STDOUT_FILENO);

		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);
        execve(argv[0], argv, env);
        std::cerr << "Error executing PHP script" << std::endl;
		_ewor = 4;
        exit(1);
    } 
	else if (pid > 0) {
        // Parent process
        close(pipe1[0]);
		close(pipe2[1]);
			
		size_t	k = _env["CGIBODY"].size();
		
		if (_env["REQUEST_METHOD"] == "POST")
		{	
			std::cout << "la : " << _env["CGIBODY"] << std::endl;
			write(pipe1[1], _env["CGIBODY"].c_str(), k);
		}

		close(pipe1[1]);
		
		int status;
		int ret = 0;
		int i = 0;
		//wait for child process
		ret = waitpid(pid, &status, WNOHANG);
		//verify if the process is taking too much time
		while (ret != pid && i < 200)
		{
    		ret = waitpid(pid, &status, WNOHANG);
    		std::this_thread::sleep_for(std::chrono::milliseconds(10));
    		i++;
		}
		//kill child process if timelimit is reached
		if (i == 200)
		{
			_ewor = 5;
			kill(pid, SIGTERM);
		}
		// Read the output from the read end of the pipe
		char buffer[10000];
        ssize_t bytesRead;
        while ((bytesRead = read(pipe2[0], buffer, sizeof(buffer))) > 0) {
            output.append(buffer, bytesRead);
        }
        close(pipe2[0]);

         if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            // std::cout << "Output of PHP script:" << std::endl;
            // std::cout << output << std::endl;
        } else {
            std::cerr << "PHP script execution failed" << std::endl;
			_ewor = 4;
			return 0;
        }       
    } 
	else {
        // Fork failed
        std::cerr << "Error forking process" << std::endl;
		_ewor = 5;
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


