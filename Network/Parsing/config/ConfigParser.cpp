/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:28:08 by mravera           #+#    #+#             */
/*   Updated: 2023/07/07 20:05:13 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"

int	ConfigParser::ConfigBuilder(char *filename) {

	std::fstream	myfile;
	std::string		buff;
	std::string		newFilename = filename;
	int				i = 1;

	this->default_server = "";
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
	if(!this->check_servers())
		throw("Error in parsing : bad server");
	return 0;
}

int	ConfigParser::videur(std::string str) {
	
	std::string			serv_n;
	std::string			token;
	std::string			elem;
	std::istringstream	ss(str);

	if(str.empty() || (str[0] == '/' && str[1] == '/'))
		return 0;
	if(ss >> serv_n && ss >> token) {
		if(token != "add") {
			if(this->servec.find(serv_n) == this->servec.end())
				this->addServ(serv_n);
			this->addTruc(serv_n, token, ss);
		}
		else
			this->addTruc(serv_n, token, ss);
	}
	else
		throw("Error : too fiew elements in configuration file.");
	return 0;
}

int	ConfigParser::isToken(std::string token) {

	std::string			serv_token = "abcdex";
	std::string			route_token = "abcdefgh";

	if((token.size() != 2) || (serv_token.find(token[0]) == std::string::npos) || (route_token.find(token[1]) == std::string::npos))
		return 0;
	return 1;
}

int	ConfigParser::addTruc(std::string servname, std::string token, std::istringstream& ss) {

	std::string	buf;
	bool		boolbuf;
	std::string route;

	if(token == "server_names") {
		while(ss >> buf)
			this->servec[servname].a_server_names.push_back(buf);
	}
	else if(token == "ports" && ss >> buf) {
		if(this->check_port(buf))
			this->servec[servname].b_port.push_back(buf);
	}
	else if(token == "max_body_size" && ss >> buf)
		this->servec[servname].d_max_body_size = buf;
	else if(token == "back_log" && ss >> buf) {
		if(this->check_back_log(servname, buf))
			this->servec[servname].e_back_log = buf;
	}
	else if(token[0] == '_' && ss >> route) {
		this->addRoute(servname, route);
		if(token == "_route" && ss >> buf) {
			if(buf[0] != '/')
				buf = '/' + buf;
			this->servec[servname].c_routes[route].a_route = route;
		}
		else if(token == "_methods")
			while(ss >> buf)
				this->servec[servname].c_routes[route].b_methods.push_back(buf);
		else if(token == "_redirection" && ss >> buf) {
			if(buf[0] != '/')
				buf = '/' + buf;
			this->servec[servname].c_routes[route].c_redirec = buf;
		}
		else if(token == "_root" && ss >> buf) {
			if(buf[0] != '/')
				buf = '/' + buf;
			this->servec[servname].c_routes[route].d_root = buf;
		}
		else if(token == "_rep_listing" && ss >> boolbuf)
			this->servec[servname].c_routes[route].e_rep_listing = boolbuf;
		else if(token == "_def_rep" && ss >> buf) {
			if(buf[0] != '/')
				buf = '/' + buf;
			this->servec[servname].c_routes[route].f_def_rep = buf;
		}
		else if(token == "_cgi_script" && ss >> buf) {
			if(buf[0] != '/')
				buf = '/' + buf;
			this->servec[servname].c_routes[route].g_cgi_script = buf;
		}
		else if(token == "_cgi_addr" && ss >> buf) {
			if(buf[0] != '/')
				buf = '/' + buf;
			this->servec[servname].c_routes[route].h_cgi_addr = buf;
		}
	}
	else if(token == "add" && ss >> buf)
		this->x_error_names[servname] = buf;
	else
		throw("Error : wrong token in configuration file");
	return 0;
}

int	ConfigParser::addServ(std::string name) {

	t_serv	a;
	t_route	b;

	if(this->servec.find(name) == this->servec.end()) {
		a.d_max_body_size = "";
		a.e_back_log = "40";
		if(this->default_server.empty())
			this->default_server = name;
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

int	ConfigParser::check_port(std::string str) {

	if ((str.size() > 5) || (atoi(str.c_str()) <= 1) || (atoi(str.c_str()) >= 49151) || (str.find_first_not_of("0123456789") != std::string::npos)) {
		std::cout << "Invalid port in configuration file. Using default 8080." << std::endl;
		return 0;
	}
	return 1;
}

int	ConfigParser::check_back_log(std::string servname, std::string str) {

	if (str.find_first_not_of("0123456789") != std::string::npos) {
		std::cout << "Cannot read backlog value, value set to default (40)." << std::endl;
		return 0;
	}
	if (str.size() > 5 || (atoi(str.c_str()) > 32767)) {
		std::cout << "Backlog higher than 32767, value set to 32767." << std::endl;
		this->servec[servname].e_back_log = "32767";
		return 0;
	}
	return 1;
}

int	ConfigParser::check_servers(void) {
	
	t_route	a;

	a.a_route = "/";
	a.b_methods.push_back("GET");
	a.b_methods.push_back("POST");
	a.d_root = "/Network/HtmlFiles";
	a.f_def_rep = "/pb.html";
	for(std::map<std::string, t_serv>::iterator it = this->servec.begin(); it != this->servec.end(); it++) {
		std::cout << "checking [" << it->first << "] ..." << std::endl;
		if(it->second.c_routes.find("/") == it->second.c_routes.end()) {
			it->second.c_routes["/"] = a;
			std::cout << "default route added to " << it->first << std::endl;
		}
		if(it->second.c_routes["/"].d_root.empty())
			throw("Error in configuration file : every route needs a root route!");
		for(std::map<std::string, t_route>::iterator itt = it->second.c_routes.begin(); itt != it->second.c_routes.end(); itt++) {
			if((itt->second.e_rep_listing == 0) && itt->second.f_def_rep.empty())
				throw("Error no def_rep set up with listing set to 0 in configuration file.");
		}
	}
	return 1;
}

int ConfigParser::dispConfig(void) {

	std::cout << "-----" << std::endl << "Current config file contains : " << std::endl;
	std::cout << "default server = " << this->default_server << std::endl;
	for(std::map<std::string, t_serv>::iterator it = this->servec.begin(); it != this->servec.end(); it++) {
		std::cout << "[" << it->first << "]" << std::endl;
		std::cout << "| server_names : ";
		for(std::vector<std::string>::iterator itsn = it->second.a_server_names.begin(); itsn != it->second.a_server_names.end(); ++itsn)
			std::cout << "'" << *itsn << "' ";
		std::cout << std::endl;
		for(size_t i = 0; i < it->second.b_port.size(); i++)
			std::cout << "| port : " << it->second.b_port[i] << std::endl;
		if(!it->second.d_max_body_size.empty())
			std::cout << "| maxbdysize : " << it->second.d_max_body_size << std::endl;
		if(!it->second.e_back_log.empty())
			std::cout << "| back_log : " << it->second.e_back_log << std::endl;
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

int	ConfigParser::BuildDefault(void) {

	std::cout << "Building Default congiguration..." << std::endl;
	this->addServ("defaultServer");
	return 0;
}

int	ConfigParser::dispErrorNames(void) {
	
	std::cout << "---list of all error names in memory : ---" << std::endl;
	for(std::map<std::string, std::string>::iterator it = this->x_error_names.begin(); it != this->x_error_names.end(); it++)
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

	this->servec = rhs.servec;
	this->x_error_names = rhs.x_error_names;
	this->default_server = rhs.default_server;
	return (*this);
}

ConfigParser::~ConfigParser(void) {

	return ;
}
