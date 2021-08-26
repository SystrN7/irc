/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:23:06 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/26 14:47:17 by fgalaup          ###   ########lyon.fr   */
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

int		Connection::sendResponce(Responce &message)
{
	ssize_t		status;

	status = send(this->_fd, message.getMessage().c_str(), message.getMessage().size(), 0);
	if (status < 0)
		Logging::SystemError("[Connection] - The server fails to send data to the client");
	return (status);
}


/**
 * La valeur de retour sera 0 si le pair a effectué un arrêt normal
 * weechat -> /exit retour = -1 Connection interompue brutalement
 * weechat -> /close retour = 0 Connection interompue normalement
 * En cas d'erreur il faut sortir le FD du client de la liste de FD à monitorer
 **/
Request *Connection::receiveRequest()
{
	bool	first = true;
	int		length;
	char	buffer = '\0';
	string	message;

	message = this->_read_buffer;
	this->_read_buffer.clear();

	// // STD BUG FIX (because why not ^_^)
	// if (message.size() == 0)
	// 	message.append(" ");

	while (0 == 0)
	{
		length = recv(this->_fd, &buffer, 1, 0);
		if (length < 0 && errno == EAGAIN)
		{
			Logging::Warning("[Connection] - Partial Command");
			break;
		}
		if (length < 0)
		{
			Logging::SystemWarning("[Connection] - Client has unexpectedly closed the connection");
			return (NULL);
		}
		else if (length == 0 && first)
		{
			Logging::Info("[Connection] - Client Disconnected from Server.");
			return (NULL);
		}
		if (length == 0)
			break;
		
		message.append(1, buffer);
		if (buffer == '\n')
			break;
		first = false;
	}
	cout << "Lenght = " << length << endl;
	if (message.size() >= Connection::MAX_IRC_MESSAGES_LENGTH)
	{
		Logging::Warning("[Connection] - Message from client was refused because it exceeded the maximum length of 512 characters.");
		return (NULL);
	}

	if (length == -1)
	{
		this->_read_buffer.clear();
		this->_read_buffer = message;
		return (NULL);
	}
	
	return (new Request(*this , message));
}

Client	&Connection::getClient() { return (this->_client); };