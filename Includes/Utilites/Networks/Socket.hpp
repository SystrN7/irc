/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:02:18 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/19 18:10:13 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Core/Logging.hpp"

#include "Connection.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <fcntl.h>

#include <string>

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
