/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:44:19 by pyammoun          #+#    #+#             */
/*   Updated: 2023/07/03 17:30:19 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP 

# include <map> 
# include <iostream>
# include <string> 
# include <sstream>
# include <istream>
# include "../Server/TestServer.hpp"
# include "../Utils/Utils.hpp"

# define CGI_BUFSIZE 65536
# define CGI_FILEPATH "../Network/CGI/"

# define MAP_STRING std::map<std::string, std::string> 

class	CGI {
	public :
		
		CGI(const MAP_STRING &_requestInfo, const MAP_STRING &_responsContent);
		~CGI(void);	

		std::string	extractQueryString(const std::string &url);
		std::string	extractScriptName(const std::string &url);
		std::string	extractPathInfo(const std::string &url);
		char**		getEnvAsCstrArray(void) const;
		std::string	Exec();
		
	private:
		
		MAP_STRING		_env;
		std::string		_body;
		CGI();	
		void	setUpEnv(const MAP_STRING &_requestInfo, const MAP_STRING &_responsContent);
	
	
};
#endif