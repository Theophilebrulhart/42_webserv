/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeadersDelete.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:07:17 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/07 14:51:10 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETE_HPP
# define DELETE_HPP

# include <cstdio>
# include "../HeadersMethod.hpp"
# include "../../Parsing/HeadersParsing.hpp"
# define MAP_STRING std::map<std::string, std::string> 

//********DeleteFile*******//

void deleteFile(MAP_STRING &info, MAP_STRING &responsContent, ConfigParser::t_serv servInfo);

#endif