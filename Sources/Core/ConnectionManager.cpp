/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 14:52:50 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/26 18:21:57 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Core/ConnectionManager.hpp"

ConnectionManager::ConnectionManager(void):
	_registred_socket(),
	_registred_connection(),
	_send_queue(),
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

	for (list<Socket *>::iterator it = this->_registred_socket.begin(); it != this->_registred_socket.end(); it++)
		delete *it;
	this->_registred_socket.clear();

	for (list<Responce *>::iterator it = this->_send_queue.begin(); it != this->_send_queue.end(); it++)
		delete *it;
	this->_send_queue.clear();

	for (list<Connection *>::iterator it = this->_registred_connection.begin(); it != this->_registred_connection.end(); it++)
		delete *it;
	this->_registred_connection.clear();
}

void	ConnectionManager::registerSocket(Socket *socket)
{
	this->_registred_socket.push_back(socket);
}

void	ConnectionManager::registerConnection(Connection *connection)
{
	this->_registred_connection.push_back(connection);
}

void	ConnectionManager::addResponceToSendQueue(Responce *responce)
{
	this->_send_queue.push_back(responce);
}

void	ConnectionManager::removeConnection(Connection *connection)
{
	this->_registred_connection.remove(connection);
	delete connection;
}

void ConnectionManager::refreshMonitoredFileDescriptor()
{
	// Clear previous fds
	FD_ZERO(&this->_read_fds);
	FD_ZERO(&this->_write_fds);

	// Add socket fds (listen)
	for (list<Socket *>::iterator it = this->_registred_socket.begin(); it != this->_registred_socket.end(); it++)
		FD_SET((*it)->fd_socket, &this->_read_fds);

	// Add Connection (read)
	for (list<Connection *>::iterator it = this->_registred_connection.begin(); it != this->_registred_connection.end(); it++)
		FD_SET((*it)->_fd, &this->_read_fds);

	// Add send queue (write)
	for (list<Responce *>::iterator it = this->_send_queue.begin(); it != this->_send_queue.end(); it++)
		FD_SET((*it)->getConnection()._fd, &this->_write_fds);
}

#include <iostream>
#include <fstream>
#include <sstream>

Request		*ConnectionManager::NetworkActivitiesHandler()
{
	while (0 == 0)
	{
		this->refreshMonitoredFileDescriptor();
		if (select(FD_SETSIZE, &this->_read_fds, &this->_write_fds, NULL, NULL) <= 0)
			Logging::SystemFatal("[Select]-Fd monitoring failed");
		
		// Check socket (incoming connection)
		for (list<Socket *>::iterator it = this->_registred_socket.begin(); it != this->_registred_socket.end(); it++)
		{
			if (FD_ISSET((*it)->fd_socket, &this->_read_fds))
			{
				cout << "[+]-[Connection](Client)-New client request." << endl;
				Connection	*connection = (*it)->getConnection();
				this->registerConnection(connection);
			}
		}

		// Check Sending Queue (Write)
		list<Responce *>::iterator it = this->_send_queue.begin();
		list<Responce *>::iterator ite = this->_send_queue.end();
		while (it != ite)
		{
			if(FD_ISSET((*it)->getConnection()._fd, &this->_write_fds))
			{
				Responce	*responce;

				cout << "[>]-(Server)-Send Messages." << endl;
				responce = *it;
				responce->getConnection().sendResponce(*responce);

				this->_send_queue.remove(responce);
				delete responce;

				it = this->_send_queue.begin();
				ite = this->_send_queue.end();
			}
			it++;
		}

		// Check incoming Request (reading)
		for (list<Connection *>::iterator it = this->_registred_connection.begin(); it != this->_registred_connection.end(); it++)
		{
			if (FD_ISSET((*it)->_fd, &this->_read_fds))
			{
				try
				{
					list <Request *> requests = (*it)->receiveRequest();

					this->_recv_queue.insert(this->_recv_queue.end(), requests.begin(), requests.end());
					cout << "[<]-(Client)-Recive Request" << endl;
				}
				catch(const Connection::CloseException& e)
				{
					Logging::Info(e.what());
					// Remove conection and delete pointer
					this->removeConnection(*it);
					it = this->_registred_connection.begin();
				}
			}
		}

		if (this->_recv_queue.size() > 0)
		{
			Request	*request;
			request = this->_recv_queue.front();
			this->_recv_queue.pop_front();
			return (request);
		}
	}
}
