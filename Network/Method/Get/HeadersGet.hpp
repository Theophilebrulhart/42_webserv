/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeadersGet.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:24:03 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/07 18:24:45 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_HPP
# define GET_HPP

# include "../HeadersMethod.hpp"
# include <dirent.h>
#include <fstream>
# include "../../Parsing/HeadersParsing.hpp"
# include "../../CGI/CGI.hpp"
# define MAP_STRING std::map<std::string, std::string> 

//********OpenFile*******//

void    openFile(MAP_STRING info, MAP_STRING &responsContent, ConfigParser::t_serv &servInfo);

//********GetFile*******//

std::string				getFileToLoad(MAP_STRING &info, ConfigParser::t_route &route);

#endif