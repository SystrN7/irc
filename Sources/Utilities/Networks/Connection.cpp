/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:23:06 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/13 15:45:47 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Utilites/Networks/Connection.hpp"

Connection::Connection(int fd, struct sockaddr_in address): _fd(fd), _client_address(address)
{ }

Connection::~Connection(void)
{ close(this->_fd); }

void	Connection::printInfo()
{
	printf("IP address is: %s\n", inet_ntoa(this->_client_address.sin_addr));
	printf("Port is: %d\n", (int) ntohs(this->_client_address.sin_port));
}

// ! remove later
#include <exception>

int		Connection::sendData(const char *buffer, int lenght)
{
	ssize_t		status;

	status = send(this->_fd, buffer, lenght, 0);
	if (status < 0)
		throw exception();
	
	return (status);
}

#include <cstring>

#include <iostream>

char	*Connection::receiveData()
{
	int		lenght = 1024 - 1;
	char		buffer[1024];
	char		*result;

	lenght = recv(this->_fd, buffer, lenght, 0);
	std::cout << lenght << std::endl;
	if (lenght < 0)
	{
		perror("Error: ");
		return (NULL);
	}
	
	buffer[lenght] = '\0';
	
	result = new char[lenght + 1];
	strcpy(result, buffer);

	return (result);
}
