/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 14:52:50 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/23 13:58:20 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Core/ConnectionManager.hpp"

ConnectionManager::ConnectionManager(void):
	_registred_socket(),
	_registred_connection(),
	_sendQueue(),
	_read_fds(),
	_write_fds()
{
	FD_ZERO(&this->_read_fds);
	FD_ZERO(&this->_write_fds);
}

ConnectionManager::~ConnectionManager(void)
{
	FD_ZERO(&this->_read_fds);
	FD_ZERO(&this->_write_fds);
}

void	ConnectionManager::registerSocket(Socket *socket)
{
	this->_registred_socket.push_back(socket);
}

void	ConnectionManager::registerConnection(Connection *connection)
{
	this->_registred_connection.push_back(connection);
}

void	ConnectionManager::monitorSocket()
{
	for (list<Socket *>::iterator it = this->_registred_socket.begin(); it != this->_registred_socket.end(); it++)
		FD_SET((*it)->fd_socket, &this->_read_fds);
}

void	ConnectionManager::addResponceToSendQueue(Responce *responce)
{
	// Register file descriptor to write monitored fd
	FD_SET(responce->getConnection()._fd, &this->_write_fds);

	std::cout << "RESPONCE ADDED TO QUEUE" << std::endl;

	this->_sendQueue.push_back(responce);
}

#include <iostream>
#include <fstream>
#include <sstream>

Request		*ConnectionManager::NetworkActivitiesHandler()
{
	while (0 == 0)
	{
		std::cout << "Before Select" << std::endl;
		this->monitorSocket();
		if (select(FD_SETSIZE, &this->_read_fds, &this->_write_fds, NULL, NULL) <= 0)
			Logging::SystemFatal("[Select]-Fd monitoring failed");
		std::cout << "After Select" << std::endl;
		
		// Check socket (incoming connection)
		for (list<Socket *>::iterator it = this->_registred_socket.begin(); it != this->_registred_socket.end(); it++)
		{
			if (FD_ISSET((*it)->fd_socket, &this->_read_fds))
			{
				cout << "[+]-[Connection](Client)-New client request." << endl;
				Connection	*connection = (*it)->getConnection();
				this->registerConnection(connection);
				FD_SET(connection->_fd, &this->_read_fds);
				// FD_SET(connection->_fd, &this->_write_fds);
			}
		}

		// Check Sending Queue (Write)
		list<Responce *>::iterator it = this->_sendQueue.begin();
		list<Responce *>::iterator ite = this->_sendQueue.end();
		while (it != ite)
		{
			if(FD_ISSET((*it)->getConnection()._fd, &this->_write_fds))
			{
				cout << "[>]-(Server)-Send Messages." << endl;
				(*it)->getConnection().sendResponce(**it);

				FD_CLR((*it)->getConnection()._fd, &this->_write_fds);
				this->_sendQueue.remove((*it));

				it = this->_sendQueue.begin();
				ite = this->_sendQueue.end();
			}
			it++;
		}

		// Check incoming Request (reading)
		for (list<Connection *>::iterator it = this->_registred_connection.begin(); it != this->_registred_connection.end(); it++)
		{
			if (FD_ISSET((*it)->_fd, &this->_read_fds))
			{
				cout << "[<]-(Client)-Recive Request" << endl;
				return ((*it)->receiveRequest());
			}
		}

		// ! FIND WHI IS NOT WORKING 
		/*
		for (list<Responce *>::iterator it = this->_sendQueue.begin(); it != this->_sendQueue.end(); it++)
		{

			if(FD_ISSET((*it)->getConnection()._fd, &this->_write_fds))
			{
				cout << "[>]-(Server)-Send Messages." << endl;
				(*it)->getConnection().sendResponce(**it);

				FD_CLR((*it)->getConnection()._fd, &this->_write_fds);
				this->_sendQueue.remove((*it));
				//it = this->_sendQueue.begin();
				
				
				// ? To Move : Unregister Connected fd add function for connection reset by client
				// delete (*it);
				// this->_registred_connection.remove(*it);
				// it = this->_registred_connection.begin();
			}
		}
*/
	}
}
