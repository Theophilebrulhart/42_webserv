/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateRespons.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:37:34 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/28 15:44:03 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CreateRespons.hpp"

RESPONS::CreateRespons::CreateRespons(MAP_STRING &info) : _info(info)
{
	if (_info.at("TYPE").find("text") != std::string::npos || _info.at("TYPE").find("image") != std::string::npos)
	{
		GetResponsContentFile(_info.at("PATH"));
		setRespons(_status);
		setRespons(_contentType);
		//setRespons(_contentLength);
		setRespons("\r\n");
	}
	setRespons(_contentFile);
    return ;
}

RESPONS::CreateRespons::~CreateRespons(void)
{
    return ;
}

void	RESPONS::CreateRespons::setRespons(std::string const value)
{
	if (_respons.empty())
		_respons = value;
	else
		_respons += value;
	return ;
}

std::string RESPONS::CreateRespons::getRespons(void) const
{
	return (_respons);
}

void		RESPONS::CreateRespons::GetResponsContentFile(std::string const &file)
{
	RESPONS::GetResponsContent htmlFile(_info, file);
	RESPONS::GetStatus	status(_info, htmlFile.getContent());
	setStatus(status.getStatus());
	setContentType(htmlFile.getContentType());
	setHtmlFile(htmlFile.getContent());
	setContentLength(htmlFile.getContentLength());
	return ;
}

void	RESPONS::CreateRespons::setHtmlFile(std::string const &htmlFile)
{
	_contentFile = htmlFile;
	return ;
}

void	RESPONS::CreateRespons::setStatus(std::string const &status)
{
	_status = status;
	return ;
}

void	RESPONS::CreateRespons::setContentType(std::string const &contentType)
{
	_contentType = contentType;
	return ;
}

void	RESPONS::CreateRespons::setContentLength(std::string const &contentLength)
{
	_contentLength = contentLength;
	return ;
}