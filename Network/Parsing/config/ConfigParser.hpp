/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:35:48 by mravera           #+#    #+#             */
/*   Updated: 2023/07/04 12:10:40 by mravera          ###   ########.fr       */
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

	ConfigParser(void);
	ConfigParser(ConfigParser const & src);
	ConfigParser & operator=(ConfigParser const & rhs);
	~ConfigParser(void);

private:

	std::map<std::string, std::map<std::string, std::string> >	myServers;

	int	BuildDefault(void);
	int	videur(std::string buff);

};

#endif
