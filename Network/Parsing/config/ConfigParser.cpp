/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:28:08 by mravera           #+#    #+#             */
/*   Updated: 2023/07/06 11:46:08 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Very basic parser for weird configuration file
//Each line should contain the whole "path" leading to where the information
//will be stored.
#include "ConfigParser.hpp"

int	ConfigParser::ConfigBuilder(char *filename) {

	std::fstream	myfile;
	std::string		buff;
	std::string		newFilename = filename;
	int				i = 1;

	if (filename == NULL) {
		std::cout << "No configuration file provided : loading default settings..." << std::endl;
		BuildDefault();
		return 0;
	}
	newFilename = "Source/ConfigFiles/" + newFilename;
	
	std::cout << "Opening file   [" << newFilename << "]" << std::endl;
	myfile.open(newFilename, std::ios::in);
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
		if(videur(buff))
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
	
	std::string			serv_n;
	std::string			token;
	std::string			elem;
	std::string			serv_token = "abcde";
	std::string			route_token = "abcdefgh";
	std::istringstream	ss(str);

	if(str.empty() || (str[0] == '/' && str[1] == '/'))
		return 0;
	if(ss >> serv_n) {
		if(this->servec.find(serv_n) == this->servec.end())
			this->addServ(serv_n);
	}
	if(ss >> token) {
		if( (token.size() != 2) || (serv_token.find(token[0]) == std::string::npos) || (route_token.find(token[1]) == std::string::npos) )
			throw("Error : wrong token in configuration file");
		else
			this->addTruc(serv_n, token, ss);
	}
	else
		throw("Error : too fiew elements in configuration file.");
	return 0;
}

int	ConfigParser::addServ(std::string name) {

	t_serv	a;

	if(this->servec.find(name) == this->servec.end()) {
		a.b_port = "8080";
		a.d_max_body_size = "";
		this->servec[name] = a;
	}
	return 0;
}

int	ConfigParser::addRoute(std::string servname, std::string route) {

	t_route	a;
	
	if(this->servec[servname].c_routes.find(route) == this->servec[servname].c_routes.end()) {
		a.a_route = route;
		a.c_redirec = "";
		a.d_root = "";
		a.e_rep_listing = 0;
		a.f_def_rep = "";
		this->servec[servname].c_routes[route] = a;
	}
	return 0;
}

int	ConfigParser::addTruc(std::string servname, std::string token, std::istringstream& ss) {

	std::string	buf;
	bool		boolbuf;
	std::string route;

	if(token[0] == 'a') {
		while(ss >> buf)
			this->servec[servname].a_server_names.push_back(buf);
	}
	else if(token[0] == 'b' && ss >> buf)
		this->servec[servname].b_port = buf;
	else if(token[0] == 'd' && ss >> buf)
		this->servec[servname].d_max_body_size = buf;
	else if(token[0] == 'e' && ss >> buf && ss >> route)
		this->e_error_names[buf] = route;
	else if(token[0] == 'c' && ss >> route) {
		this->addRoute(servname, route);
		if(token[1] == 'a' && ss >> buf)
			this->servec[servname].c_routes[route].a_route = route;
		else if(token[1] == 'b')
			while(ss >> buf)
				this->servec[servname].c_routes[route].b_methods.push_back(buf);
		else if(token[1] == 'c' && ss >> buf)
			this->servec[servname].c_routes[route].c_redirec = buf;
		else if(token[1] == 'd' && ss >> buf)
			this->servec[servname].c_routes[route].d_root = buf;
		else if(token[1] == 'e' && ss >> boolbuf)
			this->servec[servname].c_routes[route].e_rep_listing = boolbuf;
		else if(token[1] == 'f' && ss >> buf)
			this->servec[servname].c_routes[route].f_def_rep = buf;
		else if(token[1] == 'g' && ss >> buf)
			this->servec[servname].c_routes[route].g_cgi_script = buf;
		else if(token[1] == 'h' && ss >> buf)
			this->servec[servname].c_routes[route].h_cgi_addr = buf;
		else
			return 1;
	}
	return 0;
}

int ConfigParser::dispConfig(void) {

	std::cout << "-----" << std::endl << "Current config file contains : " << std::endl;
	for(std::map<std::string, t_serv>::iterator it = this->servec.begin(); it != this->servec.end(); it++) {
		std::cout << "[" << it->first << "]" << std::endl;
		std::cout << "| server_names : ";
		for(std::vector<std::string>::iterator itsn = it->second.a_server_names.begin(); itsn != it->second.a_server_names.end(); ++itsn)
			std::cout << "'" << *itsn << "' ";
		std::cout << std::endl;
		if(!it->second.b_port.empty())
			std::cout << "| port : " << it->second.b_port << std::endl;
		if(!it->second.d_max_body_size.empty())
			std::cout << "| maxbdysize : " << it->second.d_max_body_size << std::endl;
		for(std::map<std::string, t_route>::iterator itr = it->second.c_routes.begin(); itr != it->second.c_routes.end(); itr++) {
			std::cout << "| route [" << itr->first << "]" << std::endl;
			std::cout << "|   methods = ";
			for(std::vector<std::string>::iterator itmet = itr->second.b_methods.begin(); itmet != itr->second.b_methods.end(); itmet++)
				std::cout << "'" << *itmet << "' ";
			std::cout << std::endl;
			std::cout << "|   redirec = " << itr->second.c_redirec << std::endl << "|   root = " << itr->second.d_root << std::endl;
			std::cout << "|   replist = " << itr->second.e_rep_listing << std::endl << "|   defrep = " << itr->second.f_def_rep << std::endl;
			std::cout << "|   cgi_script = " << itr->second.g_cgi_script << std::endl << "|   cgi_addr = " << itr->second.h_cgi_addr << std::endl;
			std::cout << "_" << std::endl << std::endl;
		}
	}
	return 0;
}

int	ConfigParser::dispErrorNames(void) {
	
	std::cout << "---list of all error names in memory : ---" << std::endl;
	for(std::map<std::string, std::string>::iterator it = this->e_error_names.begin(); it != this->e_error_names.end(); it++)
		std::cout << it->first << "=" << it->second << std::endl;
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

//old
int	ConfigParser::videur_old(std::string str) {
	
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

int ConfigParser::dispConfig_old(void) {

	std::cout << "Current config file contains : " << std::endl;
	for(std::map<std::string, std::map<std::string, std::vector<std::string> > >::iterator it = this->myServers.begin(); it != this->myServers.end(); it++) {
	 	for(std::map<std::string, std::vector<std::string> >::iterator itt = it->second.begin(); itt != it->second.end(); itt++)
			for(std::vector<std::string>::iterator ittt = itt->second.begin(); ittt != itt->second.end(); ittt++)
				std::cout << "[" <<it->first << "] -> " << itt->first << " : " << *ittt << std::endl;
		std::cout << std::endl;
	}
	return 0;
}
