/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeadersPost.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:24:03 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/07 14:51:41 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_HPP
# define POST_HPP

# include <sys/socket.h>
# include <fstream>
# include "../HeadersMethod.hpp"
# include "../../Parsing/HeadersParsing.hpp"
# define MAP_STRING std::map<std::string, std::string> 

//********GetFormValue*******//

void    getFormValue(std::string const &content, MAP_STRING &info, MAP_STRING &responsContent,  ConfigParser::t_serv &servInfo);

//********FormParsing*******//

void    formParsing(std::string &buffer, MAP_STRING &info, int socket, MAP_STRING &responsContent, ConfigParser::t_serv &servInfo);

#endif