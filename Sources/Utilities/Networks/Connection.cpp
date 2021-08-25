/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:23:06 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/25 11:00:29 by seruiz           ###   ########lyon.fr   */
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

Request *Connection::receiveRequest()
{
	int		length = 512;
	char	buffer[512] = {0};

	length = recv(this->_fd, buffer, length, 0);
	//La valeur de retour sera 0 si le pair a effectué un arrêt normal
	//weechat -> /exit retour = -1 Connection interompue brutalement
	//weechat -> /close retour = 0 Connection interompue normalement
	//En cas d'erreur il faut sortir le FD du client de la liste de FD à monitorer
	if (length < 0)
	{
		Logging::SystemWarning("[Connection] - Client has unexpectedly closed the connection");
		return (NULL);
	}
	else if (length == 0)
	{
		Logging::Info("[Connection] - Client Disconnected from Server.");
		return (NULL);
	}
	return (
		new Request(*this ,string(buffer, length))
	);
}

Client	&Connection::getClient() { return (this->_client); };