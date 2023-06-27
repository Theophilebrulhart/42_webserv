/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindSocket.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:03:27 by tbrulhar          #+#    #+#             */
/*   Updated: 2023/03/02 13:21:57 by tbrulhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDSOCKET_HPP
# define BINDSOCKET_HPP
# include <iostream> 
# include "ASocket.hpp"

namespace SOCKET
{
	class BindSocket : public ASocket
	{
		public:
			BindSocket(int domain, int service, int protocol, int port, u_long interface);
		~BindSocket(void);

		int bindOrConnect(int socketFd, struct sockaddr_in address) const;

		private:
			
			//BindSocket(void);
			//BindSocket(BindSocket const &cpy);
			BindSocket &operator=(BindSocket const &rhs);
	};
}



#endif