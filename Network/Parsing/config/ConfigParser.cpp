/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:28:08 by mravera           #+#    #+#             */
/*   Updated: 2023/07/04 15:31:21 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Very basic parser for weird configuration file
//Each line should contain the whole "path" leading to where the information
//will be stored.
#include "ConfigParser.hpp"

int	ConfigParser::ConfigBuilder(char *filename) {

	std::fstream	myfile;
	std::string		buff;
	int				i = 1;

	if (filename == NULL) {
		std::cout << "No configuration file provided : loading default settings..." << std::endl;
		BuildDefault();
		this->dispConfig();
		return 0;
	}
	std::cout << "Opening file   [" << filename << "]" << std::endl;
	myfile.open(filename, std::ios::in);
	if (!myfile.is_open()) {
		std::cerr << "Error in function ConfigBuilder : " << strerror(errno) << std::endl;
		return 1;
	}
	std::cout << "Parsing        [" << filename << "] as configuration file" << std::endl;
	std::getline(myfile, buff);
	if (buff != "Bonjour!") {
		std::cout << "Configuration file must say 'Bonjour!' to preserve it's mother integrity." << std::endl;
		return(1);
	}
	while (std::getline(myfile, buff)) {
		try {
			videur(buff);
			i++;
		}
		catch (const char* exc) {
			std::cout << "[" << i << "] Caught exception during parsing : " << std::endl << "--> \"" << exc << "\"" << std::endl;
			return 1;
		}
	}
	this->dispConfig();
	return 0;
}

int	ConfigParser::BuildDefault(void) {

	std::cout << "Building Default congiguration..." << std::endl;
	this->myServers["myserver:8080"] ["port"] = "8080";
	this->myServers["myserver:8080"] ["server_name"] = "myserver";
	return 0;
}

int	ConfigParser::videur(std::string str) {
	
	std::string			buf;
	std::string			buff;
	std::string			bufff;
	std::istringstream	ss(str);
	std::map<std::string, std::map<std::string, std::string> >::iterator	it;
	std::map<std::string, std::string>::iterator							itt;

	if(str.empty())
		return 0;
	if(ss >> buf && ss >> buff && ss >> bufff)
		this->myServers[buf] [buff] = (bufff);
	else
		throw("Error, wrong format in configuration file.");
	return 0;
}

int ConfigParser::dispConfig(void) {

	std::cout << "Current config file contains : " << std::endl;
	for(std::map<std::string, std::map<std::string, std::string> >::iterator it = this->myServers.begin(); it != this->myServers.end(); it++) {
	 	for(std::map<std::string, std::string>::iterator itt = it->second.begin(); itt != it->second.end(); itt++)
			std::cout << "[" <<it->first << "] -> " << itt->first << " : " << itt->second << std::endl;
		std::cout << std::endl;
	}
	return 0;
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
