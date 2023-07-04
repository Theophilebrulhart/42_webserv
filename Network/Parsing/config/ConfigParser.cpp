/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:28:08 by mravera           #+#    #+#             */
/*   Updated: 2023/07/04 22:12:17 by mravera          ###   ########.fr       */
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
		return 0;
	}
	std::cout << "Opening file   [" << filename << "]" << std::endl;
	myfile.open(filename, std::ios::in);
	if (!myfile.is_open()) {
		std::cerr << "Error in function ConfigBuilder : " << strerror(errno) << std::endl;
		throw("Could not open requested file.");
		return 1;
	}
	std::cout << "Parsing        [" << filename << "] as configuration file" << std::endl;
	std::getline(myfile, buff);
	if (buff != "Bonjour!") {
		throw("Configuration file must say 'Bonjour!' to preserve it's mother integrity.");
		return(1);
	}
	while (std::getline(myfile, buff)) {
		if(videur2(buff))
			throw(i);
		i++;
	}
	if(this->servec.empty())
		throw("No server has been found in provided configuration file.");
	return 0;
}

int	ConfigParser::BuildDefault(void) {

	std::cout << "Building Default congiguration..." << std::endl;
	this->myServers["myserver:8080"]["port"].push_back("8080");
	this->myServers["myserver:8080"]["server_name"].push_back("myserver");
	return 0;
}

int	ConfigParser::videur(std::string str) {
	
	std::string			buf;
	std::string			buff;
	std::string			bufff;
	std::istringstream	ss(str);

	if(str.empty())
		return 0;
	if(ss >> buf && ss >> buff && ss >> bufff) {
		this->myServers[buf][buff].push_back(bufff);
		while(ss >> bufff)
			this->myServers[buf][buff].push_back(bufff);
	}
	else
		return 1;
	return 0;
}

int	ConfigParser::videur2(std::string str) {
	
	std::string			buf;
	std::string			buff;
	std::string			serv_token = "abc";
	std::string			route_token = "abcdef";
	std::istringstream	ss(str);

	if(str.empty())
		return 0;
	if(ss >> buf && !(buf[0] == '/' && buf[1] == '/')) {
		if(this->servec.find(buf) == this->servec.end())
			this->addServ(buf);
	}
	if(ss >> buff) {
		if( (buff.size() != 2) || (serv_token.find(buff[0]) == std::string::npos) || (serv_token.find(buff[1]) == std::string::npos) )
			throw("Error : wrong token in configuration file");
		else if(ss >> buff)
			this->addtruc(buf, buff);
	}
	else
		throw("Error : too fiew element in configuration file.");
	return 0;
}

int ConfigParser::dispConfig(void) {

	std::cout << "Current config file contains : " << std::endl;
	for(std::map<std::string, std::map<std::string, std::vector<std::string> > >::iterator it = this->myServers.begin(); it != this->myServers.end(); it++) {
	 	for(std::map<std::string, std::vector<std::string> >::iterator itt = it->second.begin(); itt != it->second.end(); itt++)
			for(std::vector<std::string>::iterator ittt = itt->second.begin(); ittt != itt->second.end(); ittt++)
				std::cout << "[" <<it->first << "] -> " << itt->first << " : " << *ittt << std::endl;
		std::cout << std::endl;
	}
	return 0;
}

int ConfigParser::dispConfig2(void) {

	std::cout << "Current config file contains : " << std::endl << std::endl;
	for(std::map<std::string, t_serv>::iterator it = this->servec.begin(); it != this->servec.end(); it++) {
		std::cout << "[" << it->first << "]" << std::endl;
		std::cout << "server_names : ";
		for(std::vector<std::string>::iterator itsn = it->second.a_server_names.begin(); itsn != it->second.a_server_names.end(); ++itsn) {
			std::cout << *itsn << " ";
			std::cout << it->first << std::endl;
			std::cout << itsn->front() << std::endl;
		}
		std::cout << std::endl;
		std::cout << "port : " << it->second.b_port << std::endl;
		for(std::map<std::string, t_route>::iterator itr = it->second.c_routes.begin(); itr != it->second.c_routes.end(); itr++) {
			std::cout << "route : " << itr->first << std::endl << "methods = " << itr->second.b_methods[0] << std::endl;
			std::cout << "redirec : " << itr->second.c_redirec << std::endl << "root = " << itr->second.d_root << std::endl;
			std::cout << "replist = " << itr->second.e_rep_listing << std::endl << "defrep = " << itr->second.f_def_rep << std::endl;
		}
	}
	return 0;
}

int	ConfigParser::addServ(std::string name) {

	t_serv	a;

	std::cout << "adding " << name << " to servec." << std::endl;
	if(this->servec.find(name) == this->servec.end()) {
		this->servec[name] = a;
		this->servec[name].b_port = "";
	}
	return 0;
}

int	ConfigParser::addtruc(std::string servname, std::string buff) {

	std::cout << "servname = " << servname << std::endl;
	std::cout << "buff     = " << buff << std::endl;
	if(buff[0] == 'a')
		this->servec[servname].a_server_names.push_back(buff);
	if(buff[0] == 'b')
		this->servec[servname].b_port = buff;
	return 0;
}

ConfigParser::ConfigParser(void) {

	this->ConfigBuilder(NULL);
	return ;
}

ConfigParser::ConfigParser(char *filename) {

	this->ConfigBuilder(filename);
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
