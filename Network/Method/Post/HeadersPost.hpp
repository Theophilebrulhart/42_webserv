/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeadersPost.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:24:03 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/28 15:18:27 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_HPP
# define POST_HPP

# include <map>
# include <iostream>
# include <unistd.h>
# include <vector>
# include <sys/socket.h>
# include <fstream>
# define MAP_STRING std::map<std::string, std::string> 

//********GetFormValue*******//

void    getFormValue(std::string const &content, MAP_STRING &info);

//********FormParsing*******//

void    formParsing(std::string &buffer, MAP_STRING &info, int socket);

#endif