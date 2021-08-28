/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:47:10 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/28 13:29:28 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Core/Logging.hpp"

#include "Resources/Request.hpp"
#include "Resources/Responce.hpp"
#include "Resources/Client.hpp"

#include <unistd.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include <list>
#include <string>
#include <exception>


class Request;

using namespace std;

class Connection
{
	static const int MAX_IRC_MESSAGES_LENGTH = 512;

	private:
		int					_fd;
		struct sockaddr_in	_client_address;
		string				_read_buffer;
		Client				_client;

	private:
		Connection(void);
		Connection(const Connection &rhs);
		Connection			&operator=(const Connection &rhs);
		

	public:
		Connection(int fd, struct sockaddr_in address);
		~Connection(void);

		void	printInfo();
		list<Request *>receiveRequest();
		int	sendResponce(Responce &message);
		Client	&getClient();

	friend class ConnectionManager;

	// Exception
	class CloseException: public exception
	{
		public:
			virtual const char *what(void) const throw()
			{ return ("Client close connection"); }
	};

	class PartialMessageException: public exception
	{
		public:
			virtual const char *what(void) const throw()
			{ return ("Partial command recive."); }
	};

};