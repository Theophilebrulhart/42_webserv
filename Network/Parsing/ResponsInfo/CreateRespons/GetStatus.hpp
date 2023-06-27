/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetStatus.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:05:16 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/03/10 14:51:04 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETSTATUS_HPP
# define GETSTATUS_HPP

# include "../ResponsInfo.hpp"
# include <map>
# include <iostream>
# define MAP_STRING std::map<std::string, std::string>

namespace RESPONS
{
	class GetStatus
	{
		public:
			GetStatus(MAP_STRING &info, std::string content);
			~GetStatus(void);

			std::string	getStatus(void) const;
			void		setStatus(std::string const &value);

		private:

			std::string	_status;
			std::string	_content;
			MAP_STRING	_info;
	};
}



#endif