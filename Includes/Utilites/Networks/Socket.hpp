/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:02:18 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/13 17:05:16 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Core/Logging.hpp"

#include "Connection.hpp"

#include <arpa/inet.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <errno.h>

#include <string>

#include <exception>

using namespace std;

class Socket
{
	private:
		int					fd_socket;
		struct sockaddr_in	socket_settings;
	
	private:
		Socket(Socket &object);
		Socket&			operator=(Socket& object);

	public:
		Socket(const unsigned short port = 194, const char *address = "0.0.0.0");
		virtual ~Socket();
		

		Connection		*getConnection(void);

	friend class ConnectionManager;
};
