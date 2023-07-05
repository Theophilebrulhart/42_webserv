/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:19:26 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/03 14:27:40 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CreateResponsUTILS_HPP
# define CreateResponsUTILS_HPP
# include <map>
# include <iostream>
# include <sstream>
# include <fstream>
# define MAP_STRING std::map<std::string, std::string> 

std::string contentExtension(std::string const &file);
void setResponsContent(MAP_STRING &responsContent, std::string protocol, std::string status,
						 std::string contentType, std::string body);
std::string ft_itoa(int n);
std::string loadContentFile(std::string contentFile);
int isValidMethod(const MAP_STRING& info);
int isInternalError( MAP_STRING &info, MAP_STRING &responsContent, std::string contentType);
#endif