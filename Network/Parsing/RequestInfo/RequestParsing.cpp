/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParsing.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:02:35 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/12 17:02:54 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HeadersRequestInfo.hpp"
# include "../../Method/HeadersMethod.hpp"

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

int tryValue(MAP_STRING info, std::string key)
{
    try
    {
        info.at(key);
    }
    catch (const std::out_of_range& oor)
    {
        std::cout << "failed with : " << key << "\n\n";
        return (-1);
    }
    return (1);
}

int infoCheck(MAP_STRING info)
{
    if (tryValue(info, "PATH") < 0)
        return (-1);
    if (tryValue(info, "METHOD") < 0)
        return (-1);
    if (tryValue(info, "PROTOCOL") < 0)
        return (-1);
    return (1);
}

int    requestParsing(std::string buffer, MAP_STRING &info)
{
    // if (!buffer.find("/favicon.ico"))
    // {
        std::cout << "*****\e[0;35mMAINPARSING BUFFER\e[0m****\n" << buffer;
        std::cout << "*****\e[0;35mMAINPARSING BUFFER END\e[0m****\n" << "\n\n"; 
    // }
    if (!buffer.empty())
    {
        getInfo(buffer, info);
        printInfo(info);
        int checkRes = infoCheck(info);
        if ( checkRes < 0)
            return (checkRes);
    }
    else
    {
        std::cout << "empty request\n";
        return (0);
    }
    return (1);
        
}
