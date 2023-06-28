/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParsing.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:02:35 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/28 15:21:22 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeadersRequestInfo.hpp"

void    printInfo(MAP_STRING &info)
{
    MAP_STRING::iterator it_b = info.begin();
    MAP_STRING::iterator it_e = info.end();

	std::cout << "*****\e[0;35mREQUEST INFO PRINT\e[0m******\n";
    while (it_b != it_e)
    {
        std::cout << it_b->first << " : " << it_b->second << "\n"; 
        ++it_b;
    }
    std::cout << "*****\e[0;35mREQUEST INFO PRINT END\e[0m******\n";
}

void    requestParsing(std::string buffer, MAP_STRING &info)
{
    std::cout << "\n\n*****\e[0;35mMAINPARSING BUFFER\e[0m****\n" << buffer << "\n";
    getInfo(buffer, info);
    printInfo(info);
}
