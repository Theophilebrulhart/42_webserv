/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateRespons.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:32:57 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/28 17:48:15 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CreateRespons_HPP
# define CreateRespons_HPP
# define MAP_STRING std::map<std::string, std::string>
# include "iostream"


class TestServer;

namespace RESPONS
{
	class CreateRespons
	{
		public:
			CreateRespons(MAP_STRING &info);
			virtual ~CreateRespons(void);
		
			
			std::string	getRespons(void) const;
			void		GetResponsContentFile(std::string const &file);
			
			void		setRespons(std::string const value);
			void		setHtmlFile(std::string const &htmlFile);
			void		setStatus(std::string const &status);
			void		setContentType(std::string const &contentType);
			void		setContentLength(std::string const &contentLength);

		private:

			std::string	_respons;
			std::string _contentFile;
			std::string	_status;
			std::string	_contentType;
			std::string	_contentLength;
			MAP_STRING	_info;
	};
}

#endif