/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:23:06 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/18 13:55:18 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Utilites/Networks/Connection.hpp"

Connection::Connection(int fd, struct sockaddr_in address): _fd(fd), _client_address(address)
{ }

Connection::~Connection(void)
{ close(this->_fd); }

void	Connection::printInfo()
{
	Logging::Debug("Client IP : ");
	Logging::Debug("Client Port : ");
	// printf("IP address is: %s\n", inet_ntoa(this->_client_address.sin_addr));
	// printf("Port is: %d\n", (int) ntohs(this->_client_address.sin_port));
}

int		Connection::sendData(const char *buffer, int lenght)
{
	ssize_t		status;

	status = send(this->_fd, buffer, lenght, 0);
	if (status < 0)
		Logging::SystemError("[Connection] - The server fails to send data to the client");
	return (status);
}

string	*Connection::receiveData()
{
	int		lenght = 512;
	char	buffer[512] = {0};

	lenght = recv(this->_fd, buffer, lenght, 0);
	if (lenght < 0)
	{
		Logging::SystemError("[Connection] - Server faild to read client send data");
		return (NULL);
	}
	
	return (new string(buffer, lenght));
}
