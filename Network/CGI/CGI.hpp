/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:44:19 by pyammoun          #+#    #+#             */
/*   Updated: 2023/07/17 17:30:22 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP 

# include <map> 
# include <iostream>
# include <string> 
# include <sstream>
# include <istream>
# include <unistd.h>
# include <thread>
# include <signal.h>
# include "../Server/TestServer.hpp"
# include "../Utils/Utils.hpp"
# include "../Method/HeadersMethod.hpp"

# define CGI_BUFSIZE 65536
# define CGI_FILEPATH "./Network/Website/CGIFiles/"
# define CGI_PHP "./Network/Website/CGIFiles/php-cgi"
# define CGI_PHPN "./Network/Website/php-cgi"
# define MAP_STRING std::map<std::string, std::string> 

class	CGI {
	public :
		
		CGI(MAP_STRING &_requestInfo,  MAP_STRING &_responsContent, ConfigParser::t_serv servInfo);
		~CGI(void);	

		std::string	extractQueryString(const std::string &url);
		std::string	extractScriptName(const std::string &url);
		std::string	extractPathInfo(const std::string &url);
		char**		getEnvAsCstrArray(void) const;
		int			Exec(MAP_STRING &_responsContent, ConfigParser::t_serv servInfo);
		int			SetResponseContent(MAP_STRING &_responsContent, std::string output);
		void 		freeEnvMemory(char** env);
		void 		freeString(char* s1, char* s2);
		
	private:
		
		MAP_STRING		_env;
		std::string		_body;
        int				_ewor;
		CGI();	
		void	setUpEnv(MAP_STRING &_requestInfo,  MAP_STRING &_responsContent, ConfigParser::t_serv servInfo);
	
	
};
#endif