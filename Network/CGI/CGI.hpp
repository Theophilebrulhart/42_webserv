/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:44:19 by pyammoun          #+#    #+#             */
/*   Updated: 2023/07/10 11:16:39 by tbrulhar         ###   ########.fr       */
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
# define MAP_STRING std::map<std::string, std::string> 

class	CGI {
	public :
		
		CGI(MAP_STRING &_requestInfo,  MAP_STRING &_responsContent);
		~CGI(void);	

		std::string	extractQueryString(const std::string &url);
		std::string	extractScriptName(const std::string &url);
		std::string	extractPathInfo(const std::string &url);
		char**		getEnvAsCstrArray(void) const;
		int			Exec(MAP_STRING &_responsContent);
		int			SetResponseContent(MAP_STRING &_responsContent, std::string output);
		
	private:
		
		MAP_STRING		_env;
		std::string		_body;
        int				_ewor;
		CGI();	
		void	setUpEnv(MAP_STRING &_requestInfo,  MAP_STRING &_responsContent);
	
	
};
#endif