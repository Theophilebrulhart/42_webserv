/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:35:48 by mravera           #+#    #+#             */
/*   Updated: 2023/07/05 21:06:48 by mravera          ###   ########.fr       */
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

	int	ConfigBuilder(char *filename);
	int	dispConfig(void);
	int	dispErrorNames(void);
	int	dispConfig_old(void);

	ConfigParser(void);
	ConfigParser(char *filename);
	ConfigParser(ConfigParser const & src);
	ConfigParser & operator=(ConfigParser const & rhs);
	~ConfigParser(void);

private:

	typedef struct s_route {

		std::string					a_route;
		std::vector<std::string>	b_methods;
		std::string					c_redirec;
		std::string					d_root;
		bool						e_rep_listing;
		std::string					f_def_rep;

	} t_route;

	typedef struct s_serv {

		std::vector<std::string>			a_server_names;
		std::string							b_port;
		std::map<std::string, t_route>		c_routes;
		std::string							d_max_body_size;

	} t_serv;

	int	addServ(std::string name);
	int	addRoute(std::string servname, std::string route);
	int	addTruc(std::string servname, std::string token, std::istringstream& ss);

	std::map<std::string, t_serv>		servec;
	std::map<std::string, std::string>	e_error_names;

	int	BuildDefault(void);
	int	videur(std::string buff);
	int	videur_old(std::string buff);

//old
	std::map<std::string, std::map<std::string, std::vector<std::string> > >	myServers;
};

#endif
