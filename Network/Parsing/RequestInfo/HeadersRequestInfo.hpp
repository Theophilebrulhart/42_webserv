/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeadersRequestInfo.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:53:21 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/28 16:58:02 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERSREQUESTINFO_HPP
# define HEADERSREQUESTINFO_HPP

# include <map>
# include <iostream>
# include <unistd.h>
# include <vector>
# include <sys/socket.h>
# include <fstream>
# include <cstdio>
# define MAP_STRING std::map<std::string, std::string> 

//********MainParsing*******//
void    requestParsing(std::string buffer, MAP_STRING &info);
void    printInfo(MAP_STRING &info);
void    formParsing(std::string &buffer, MAP_STRING &info, int socket);

//********GetInfo*******//

void	getInfo(std::string &buffer, MAP_STRING &info);
void    getMethod(std::string &buffer, MAP_STRING &info);
void	getSection(std::string &buffer, MAP_STRING &info, std::string toFind, std::string name);

//********DeleteFile*******//

void deleteFile(MAP_STRING &info, int socket);

#endif