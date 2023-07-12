/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:09:55 by mravera           #+#    #+#             */
/*   Updated: 2023/07/10 13:46:52 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

# include <iostream>
# include <string>
# include <map>
# include <vector>
# include <list>
# include <fstream>
# include <sstream>

class ConfigParser {

public:

	typedef struct s_route {

		std::string					a_route;
		std::vector<std::string>	b_methods;
		std::string					c_redirec;
		std::string					d_root;
		bool						e_rep_listing;
		std::string					f_def_rep;
		std::string					g_cgi_script;
		std::string					h_cgi_addr;

	} t_route;

	typedef struct s_serv {

		std::vector<std::string>			a_server_names;
		std::vector<std::string>			b_port;
		std::map<std::string, t_route>		c_routes;
		std::string							d_max_body_size;
		std::string							e_back_log;

	} t_serv;

	std::string							default_server;
	std::map<std::string, t_serv>		servec;
	std::map<std::string, std::string>	x_error_names;

	int	ConfigBuilder(char *filename);
	int	dispConfig(void);
	int	dispErrorNames(void);

	ConfigParser(void);
	ConfigParser(char *filename);
	ConfigParser(ConfigParser const & src);
	ConfigParser & operator=(ConfigParser const & rhs);
	~ConfigParser(void);

private:

	int			isToken(std::string);
	int			BuildDefault(void);
	int			videur(std::string buff);
	std::string	addslash(std::string str);

	int	addServ(std::string name);
	int	addRoute(std::string servname, std::string route);
	int	addTruc(std::string servname, std::string token, std::istringstream& ss);

	int	check_port(std::string str);
	int	check_back_log(std::string servname, std::string str);
	int	check_servers(void);

};

#endif
