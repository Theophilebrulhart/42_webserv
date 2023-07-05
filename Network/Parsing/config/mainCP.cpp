/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainCP.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:17:47 by mravera           #+#    #+#             */
/*   Updated: 2023/07/05 14:02:37 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"

int	main(int argc, char **argv) {

	try {
		ConfigParser a(argv[1]);
		a.dispConfig();
	}
	catch(const char* exc) {
		std::cout << "Caught exception while parsing congiguration file :  "<< std::endl << exc << std::endl;
	}
	catch(const int exc) {
		std::cout << "Caught exception : Wrong format in configuration file at line [" << exc << "]" << std::endl;
	}
	return 0;
}