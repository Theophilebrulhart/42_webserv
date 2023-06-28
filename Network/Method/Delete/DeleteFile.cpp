/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteFile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:25:27 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/06/28 15:18:57 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeadersDelete.hpp"

void deleteFile(MAP_STRING &info, int socket)
{
    std::string fileToDelete = "Network/HtmlFiles/Image/" + info.at("PATH");
    if (std::remove(fileToDelete.c_str()) != 0)
    {
        std::perror(("Failed to delete the file located at " + fileToDelete).c_str());
        
    }
    std::puts("File deleted");
}