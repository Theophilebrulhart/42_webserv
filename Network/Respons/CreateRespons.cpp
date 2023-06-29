/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateRespons.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:37:34 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/28 15:44:03 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CreateRespons.hpp"

RESPONS::CreateRespons::CreateRespons(MAP_STRING &responsContent) : _responsContent(responsContent)
{
	parseResponsContent();
    return ;
}

RESPONS::CreateRespons::~CreateRespons(void)
{
    return ;
}

void	RESPONS::CreateRespons::setRespons(std::string const value)
{
	if (_respons.empty())
		_respons = value;
	else
		_respons += value;
	return ;
}

std::string RESPONS::CreateRespons::getRespons(void) const
{
	return (_respons);
}

void RESPONS::CreateRespons::parseResponsContent(void)
{
    std::map<std::string, std::string>::const_iterator it;
    for (it = _responsContent.begin(); it != _responsContent.end(); ++it) {
        const std::string& key = it->first;
        const std::string& value = it->second;
		std::cout << "key " << key << "\n";
        
        if (key == "Aprotocol") {
            setRespons(value + " ");
        }
        else if (key == "Ebody") {
            setRespons("\r\n" + value);
        }
        else {
            setRespons(value + "\r\n");
        }
    }
}
