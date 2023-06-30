/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:44:19 by pyammoun          #+#    #+#             */
/*   Updated: 2023/06/30 14:20:54 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP 

#include <map> 
#include <iostream>
#include <string> 
#include "../Server/TestServer.hpp"

# define MAP_STRING std::map<std::string, std::string> 

class	CGI {
	public :
		
		CGI(Testserver &test);
		CGI(void);	
		
	private:
		
		MAP_STRING		_env;
		std::string		_body;
		CGI();
		void	setUpEnv(Testserver &test);
	
	
};
#endif