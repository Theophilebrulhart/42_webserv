/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:35:48 by mravera           #+#    #+#             */
/*   Updated: 2023/06/30 17:21:08 by mravera          ###   ########.fr       */
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

class ServerInfo {

public:

	ServerInfo(void);

	int									port;
	std::string 						host;
	std::map<std::string, std::string>	routes;

};

class ConfigParser {

public:

	int	ConfigBuilder(char *filename);

	ConfigParser(void);
	ConfigParser(ConfigParser const & src);
	ConfigParser & operator=(ConfigParser const & rhs);
	~ConfigParser(void);

private:

	int							BuildDefault(void);
	int							videur(std::string buff);

	std::vector<ServerInfo>		myServers;

};

#endif
