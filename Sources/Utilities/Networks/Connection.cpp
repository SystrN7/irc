/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:23:06 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/28 13:29:55 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Utilites/Networks/Connection.hpp"

Connection::Connection(int fd, struct sockaddr_in address): 
	_fd(fd),
	_client_address(address), 
	_read_buffer(),
	_client()
{ }

Connection::~Connection(void)
{
	close(this->_fd);
}

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
list<Request *>Connection::receiveRequest()
{
	char	buffer[10000] = {0};
	ssize_t	length = 0;
	string	message;
	size_t	message_lenght = 0;
	list<Request *>	message_queue;

	message = this->_read_buffer;

	length = recv(this->_fd, buffer, 10000, 0);

	if (length == -1 || length == 0)
		throw Connection::CloseException();

	cout << "=======1==========" << endl;
	message.append(buffer, length);


	while ((message_lenght = message.find("\n")) != string::npos)
	{
		message_lenght += 1;
		if (message_lenght > 512)
			Logging::Warning("[Connection] - Message from client was refused because it exceeded the maximum length of 512 characters.");
		else if (message_lenght > 1)
		{
			string unic_message = message.substr(0, message_lenght);
			if (unic_message[(unic_message.size() - 2)] != '\r')
				unic_message.insert(message_lenght - 1, 1, '\r');
			message_queue.push_back(new Request(*this, unic_message));
		}

		message.erase(0, message_lenght);
	}

	cout << "=======2==========" << endl;

	this->_read_buffer = message;

	return (message_queue);
}

Client	&Connection::getClient() { return (this->_client); };