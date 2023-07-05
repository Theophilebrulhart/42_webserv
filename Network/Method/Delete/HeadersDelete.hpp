/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeadersDelete.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:07:17 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/29 15:14:00 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETE_HPP
# define DELETE_HPP

# include <map>
# include <iostream>
# include <unistd.h>
# include <cstdio>
# define MAP_STRING std::map<std::string, std::string> 

//********DeleteFile*******//

void deleteFile(MAP_STRING &info, MAP_STRING &responsContent);

#endif