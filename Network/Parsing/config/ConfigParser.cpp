/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:28:08 by mravera           #+#    #+#             */
/*   Updated: 2023/06/30 17:22:25 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Very basic parser for weird configuration file
//Each line should contain the whole "path" leading to where the information
//will be stored.
#include "ConfigParser.hpp"

int	ConfigParser::ConfigBuilder(char *filename) {

	std::fstream	myfile;
	std::string		buff;

	if (filename == NULL) {
		std::cout << "No configuration file provided : loading default settings..." << std::endl;
		BuildDefault();
		return 0;
	}
	std::cout << "Opening file   [" << filename << "]" << std::endl;
	myfile.open(filename, std::ios::in);
	if (!myfile.is_open()) {
		std::cerr << "Error in function CPexe: " << strerror(errno) << std::endl;
		return 1;
	}
	std::cout << "Parsing        [" << filename << "] as configuration file" << std::endl;
	std::getline(myfile, buff);
	videur(buff);
	return 0;
}

int	ConfigParser::BuildDefault(void) {

	std::cout << "***** WIP Building Default congiguration in  ******" << std::endl;
	this->myServers.push_back(ServerInfo());
	std::cout << "***** WIP Building Default congiguration out ******" << std::endl;
	return 0;
}

int	ConfigParser::videur(std::string buff) {
	
	std::cout << "***** WIP videur in  *****" << std::endl;
	std::cout << "videur buff = " << buff << std::endl;
	std::cout << "***** WIP videur out *****" << std::endl;
	return 0;
}

ServerInfo::ServerInfo(void) {

	return ;
}

ConfigParser::ConfigParser(void) {
	return ;
}

ConfigParser::ConfigParser(ConfigParser const & src) {

	*this = src;
	return ;
}

ConfigParser & ConfigParser::operator=(ConfigParser const & rhs) {

	this->myServers = rhs.myServers;
	return (*this);
}

ConfigParser::~ConfigParser(void) {

	return ;
}
