/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetResponsContent.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:25:04 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/03/10 11:32:54 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GetResponsContent_HPP
# define GetResponsContent_HPP
# include <fstream>
# include "GetStatus.hpp"
# include <map>
# include <iostream>
# include "Utils.hpp"
# define MAP_STRING std::map<std::string, std::string>

namespace RESPONS
{
	class GetResponsContent
	{
		public:
			GetResponsContent(MAP_STRING	&info, std::string const &file);
			~GetResponsContent(void);

			std::string	getContent(void) const;
			std::string getContentType(void) const;
			std::string	getContentLength(void) const;
			
			std::string	loadContentFile(std::string htmlFile, MAP_STRING const &info);
			void		setContentType(MAP_STRING const &info, std::string const &file);
			void		setExtension(void);
			void		setSportImage(void);

		private:

			std::string	_content;
			std::string	_contentType;
			std::string	_contentLength;
			MAP_STRING	_info;
			MAP_STRING	_extension;
			MAP_STRING	_sportsImage;
	};
}



#endif