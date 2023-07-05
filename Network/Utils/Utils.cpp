/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:58:28 by pyammoun          #+#    #+#             */
/*   Updated: 2023/07/03 16:29:53 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

void	PrintMap(std::map<std::string, std::string> mapo)
{
	std::map<std::string, std::string>::iterator	it;

	for (it = mapo.begin(); it != mapo.end(); it++)
		std::cout << "first : " << it->first << " second : " << it->second << std::endl;		
}

void printStringArray(char** strings) {
    if (strings == NULL) {
        printf("NULL\n");
        return;
    }

    for (int i = 0; strings[i] != NULL; i++) {
        printf("%s\n", strings[i]);
    }
}