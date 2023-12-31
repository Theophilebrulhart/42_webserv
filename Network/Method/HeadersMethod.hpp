/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeadersMethod.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:05:05 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/17 13:47:19 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERSMETHOD_HPP
# define HEADERSMETHOD_HPP

# include "Delete/HeadersDelete.hpp"
# include "Post/HeadersPost.hpp"
# include "Get/HeadersGet.hpp"
# include <map>
# include <iostream>
# include <sstream>
# include <vector>
# include <fstream>
# include <cstdlib>
# include <cstring>
# include <sys/types.h>
# include <sys/stat.h>
# include <algorithm>
# define MAP_STRING std::map<std::string, std::string> 

//********Utils*******//

std::string 			contentExtension(std::string const &file);
void 					setResponsContent(MAP_STRING &responsContent, std::string protocol, std::string status,
						 std::string contentType, std::string body);
std::string 			ft_itoa(int n);
std::string 			loadContentFile(std::string contentFile, std::string root);
ConfigParser::t_route	isRoute(MAP_STRING &info, MAP_STRING &responsContent, ConfigParser::t_serv &servInfo);
bool 					isDir(const std::string& path);

//********SetErrorFile*******//

int 			isValidMethod(const MAP_STRING& info);
int 			isInternalError( MAP_STRING &info, MAP_STRING &responsContent, std::string contentType);
void 			notFound(MAP_STRING &responsContent, ConfigParser::t_serv servInfo);
void			forbidden(MAP_STRING &responsContent, ConfigParser::t_serv servInfo);
void            forbiddenMethod(MAP_STRING &responsContent, ConfigParser::t_serv servInfo);
void 			redirection (MAP_STRING &responsContent, std::string newUrl);
void 			unprocessable(MAP_STRING &responsContent, ConfigParser::t_serv servInfo);

#endif