/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainCP.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:17:47 by mravera           #+#    #+#             */
/*   Updated: 2023/06/30 14:41:36 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"

int	main(int argc, char **argv) {

	ConfigParser a;

	if(argc > 2) {
		std::cout << "1 argument max" << std::endl;
		return 0;
	}
	if(argc == 1)
		a.ConfigBuilder(NULL);
	else
		a.ConfigBuilder(argv[1]);
	return 0;
}