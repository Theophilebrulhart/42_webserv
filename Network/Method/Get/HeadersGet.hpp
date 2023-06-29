/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeadersGet.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:24:03 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/29 16:13:50 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_HPP
# define GET_HPP

# include <map>
# include <iostream>
# include <unistd.h>
# define MAP_STRING std::map<std::string, std::string> 

//********OpenFile*******//

void    openFile(MAP_STRING info, MAP_STRING &responsContent);

//********Utils.cpp*******//

std::string	ft_itoa(int n);

#endif