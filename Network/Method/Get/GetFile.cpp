/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetFile.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyammoun <paolo.yammouni@42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:08:37 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/17 17:51:57 by pyammoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeadersGet.hpp"

std::string listingFile(std::string path)
{
    std::string fileListHTML;
    // std::cout << "path in listing file : " << path << "\n\n";
    std::ifstream file(path.c_str());
    if (file.good())
    {
        // std::cout << "listing Files : " <<  path << "\n\n";
        fileListHTML += "<html>\n";
        fileListHTML += "<body>\n";
        fileListHTML += "<ul>\n";
        
        // Extract the file name from the path
        const char* fullPath = path.c_str();
        const char* fileName = std::strrchr(fullPath, '/');
        if (fileName != NULL)
        {
            fileName++; // Move past the '/' character
        }
        else
        {
            fileName = fullPath; // Use the full path as the file name
        }
        
        fileListHTML += "<li><a href=\"";
        fileListHTML += fileName;
        fileListHTML += "\">";
        fileListHTML += fileName;
        fileListHTML += "</a></li>\n";
        
        fileListHTML += "</ul>\n";
        fileListHTML += "</body>\n";
        fileListHTML += "</html>\n";
    }
    
    return fileListHTML;
}
std::string listingDirectories(std::string path)
{
    // std::cout << "listing with path : " << path << "\n\n";
   std::string fileListHTML;

    DIR* directory = opendir(path.c_str());
    if (directory == NULL) {
        std::perror("Erreur lors de l'ouverture du dossier");
        return fileListHTML;
    }

    fileListHTML += "<html>\n";
    fileListHTML += "<body>\n";
    fileListHTML += "<ul>\n";

    dirent* file;
    while ((file = readdir(directory)) != NULL) {
        if (file->d_type == DT_REG) {
            fileListHTML += "<li><a href=\"";
            fileListHTML += file->d_name;
            fileListHTML += "\">";
            fileListHTML += file->d_name;
            fileListHTML += "</a></li>\n";
        }
    }

    fileListHTML += "</ul\n";
    fileListHTML += "</body>\n";
    fileListHTML += "</html>\n";

    closedir(directory);
    return fileListHTML;
}

std::string getFileToLoad(MAP_STRING &info, ConfigParser::t_route &route)
{
    std::string file;
    // std::cout << "getFileToLoad\n\n";
    std::string path = info.at("PATH");
    // std::cout << "route dans getFileToLoad : " << route.d_root << "\n\n";
    // std::cout << "path dans getFileToLoad : " << path << "\n\n";
	int isDirectoryTmp = isDir(route.d_root.substr(1) + path.substr(1));
    if (route.e_rep_listing)
    {
        // std::cout << "listing true\n\n";
        if (isDirectoryTmp)
            file = listingDirectories(route.d_root.substr(1) + path.substr(1));
        else
            file = loadContentFile(info.at("PATH").substr(1), route.d_root.substr(1));
        //     file = listingFile(route.d_root.substr(1) + path.substr(1));
        // std::cout << "listing file : " << file << "\n\n";
    }
    else
    {
        if (isDirectoryTmp)
        {
            std::cout << "load directory in getFileToLoad\n\n";
           file = loadContentFile(route.f_def_rep.substr(1), route.d_root.substr(1));
        }
        else
        {
            // std::cout << "laod file : path" << info.at("PATH").substr(1) << "\n\n";
            // std::cout << "laod file : root" << route.d_root.substr(1) << "\n\n";

            file = loadContentFile(info.at("PATH").substr(1), route.d_root.substr(1));
        }
    }
    
    return (file);
}
