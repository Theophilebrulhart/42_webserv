/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:44:14 by pyammoun          #+#    #+#             */
/*   Updated: 2023/06/30 14:33:55 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"


CGI::CGI() {

}

CGI::CGI(Testserver &test) {
	setUpEnv(Testserver &test);
}

CGI::~CGI(void) {

}

void	CGI::setUpEnv(Testserve &test)
{
	std::map<std::string, std::string>::iterator	it;

	_env["REDIRECT_STATUT"] = '200';
	_env["REQUEST_METHOD"] = test.
	
	
	
}