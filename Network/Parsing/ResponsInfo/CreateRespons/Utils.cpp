/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:18:08 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/03/07 20:51:32 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

static void	conversion(int n, std::string &str)
{
	int	sign;

	sign = 1;
	if (n < 0)
	{
		sign = -1;
		str += '-';
		if (n < -9)
			conversion((n / 10), str);
	}
	str += '0' + (n % 10) * sign;
	if (n > 9)
		conversion((n / 10), str);
}

static void	swap(std::string &str)
{
	std::string tmp;
	std::string::iterator it_b = str.begin();
	std::string::iterator it_e = str.end();
	while (it_e != it_b)
	{
		tmp += *it_e;
		it_e--; 
	}
	tmp += *it_e;
	str = tmp;
}

std::string	ft_itoa(int n)
{
	std::string	str;

	conversion(n, str);
	swap(str);
	return (str);
}