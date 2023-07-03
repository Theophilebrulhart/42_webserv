/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:58:28 by pyammoun          #+#    #+#             */
/*   Updated: 2023/07/03 14:17:40 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

void	PrintMap(std::map<std::string, std::string> mapo)
{
	std::map<std::string, std::string>::iterator	it;

	for (it = mapo.begin(); it != mapo.end(); it++)
		std::cout << "first : " << it->first << " second : " << it->second << std::endl;		
}

std::string	findSecond(std::string str)
{
	int	i = 1;
	for (;i != str.length() || i != '/'; i++)
		
	return (str.substr(0, i + 1));	
}