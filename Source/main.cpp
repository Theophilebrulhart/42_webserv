/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:10:19 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/07/10 14:05:12 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AllHeaders.hpp"

class mystring
{
    public: void _fill_string(std::string const &);
    private: std::string _asdf;
};

void mystring::_fill_string(std::string const & to_append)
{
    _asdf += to_append; std::cout << _asdf << '\n';
}

int main(int argc, char **argv)
{
    // mystring asdf;
    // asdf._fill_string("Jean");
    // asdf._fill_string("12345\r");

    // return 0;
    if(argc == 2) {
        try {
            ConfigParser a(argv[1]);
            a.dispConfig();
            //a.dispErrorNames();
            launch(a);
        }
        catch(const char* exc) {
            std::cout << "Caught exception while parsing congiguration file :  "<< std::endl << exc << std::endl;
        }
        catch(const int exc) {
            std::cout << "Caught exception : Wrong format in configuration file at line [" << exc << "]" << std::endl;
        }
    }
    return (0);
}