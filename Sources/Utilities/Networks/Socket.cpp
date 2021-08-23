/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 12:48:57 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/23 12:37:20 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Utilites/Networks/Socket.hpp"


Socket::Socket(const unsigned short port, const char *address)
{
	struct protoent	*protocol;

	protocol = getprotobyname("tcp");
	if (protocol == NULL)
		Logging::SystemFatal("[Socket](Creation)-Protocol Not found");

	this->fd_socket = socket(PF_INET, SOCK_STREAM, protocol->p_proto);
	if (this->fd_socket < 0)
		Logging::SystemFatal("[Socket](Creation)-Cannot create socket");

	// if (fcntl(this->fd_socket, F_SETFL, O_NONBLOCK) < 0)
	// 	Logging::SystemFatal("[Socket](Creation)-Cannot change fd to non-block state");

	int enable = 1;
	if (setsockopt(this->fd_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		Logging::SystemFatal("[Socket](Config)-Cannot allow address reusing");

	// this->socket_settings.sin_addr.s_addr = INADDR_ANY;
	this->socket_settings.sin_addr.s_addr = inet_addr(address);
	this->socket_settings.sin_family = AF_INET;
	this->socket_settings.sin_port = htons(port);

	if (bind(this->fd_socket, reinterpret_cast<struct sockaddr *>(&socket_settings), sizeof(socket_settings)))
		Logging::SystemFatal("[Socket](Binding)-Socket binding faild");
	
	if (listen(this->fd_socket, 1024))
		Logging::SystemFatal("[Socket](Listening)-Socket faild to listen port");
}

Socket::~Socket()
{
	shutdown(this->fd_socket, SHUT_RDWR); //Stop Socket new connection reception
	close(this->fd_socket);
}

Connection		*Socket::getConnection()
{
	struct sockaddr_in client_address;
	socklen_t	client_address_size = sizeof(client_address);
	int			fd;

	fd = accept(this->fd_socket, reinterpret_cast<struct sockaddr *>(&client_address), &client_address_size);
	if (fd < 0)
		Logging::SystemError("[Socket](Connection)-Faild to initialize client connection");
	return (new Connection(fd, client_address));
}
