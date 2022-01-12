/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 14:52:50 by fgalaup           #+#    #+#             */
/*   Updated: 2022/01/12 14:35:51 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Core/ConnectionManager.hpp"

ConnectionManager::ConnectionManager(void):
	_registred_socket(),
	_registred_connection(),
	_send_queue(),
	_recv_queue(),
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

	for (list<Request *>::iterator it = this->_recv_queue.begin(); it != this->_recv_queue.end(); it++)
		delete *it;
	this->_recv_queue.clear();

	for (list<Connection *>::iterator it = this->_registred_connection.begin(); it != this->_registred_connection.end(); it++)
		delete *it;
	this->_registred_connection.clear();
}

void	ConnectionManager::registerSocket(Socket *socket)
{
	FD_SET(socket->fd_socket, &this->_read_fds);
	this->_registred_socket.push_back(socket);
}

void	ConnectionManager::registerConnection(Connection *connection)
{
	FD_SET(connection->_fd, &this->_read_fds);
	this->_registred_connection.push_back(connection);
}

void	ConnectionManager::addResponceToSendQueue(Responce *responce)
{
	FD_SET(responce->getConnection()._fd, &this->_write_fds);
	this->_send_queue.push_back(responce);
}

void	ConnectionManager::removeConnection(Connection *connection)
{
	// Remove from monitored fd set
	FD_CLR(connection->_fd, &this->_read_fds);
	FD_CLR(connection->_fd, &this->_write_fds);

	// Remove Responce use this connection pending in queue list.
	list<Responce *>::iterator its = this->_send_queue.begin();
	while (its != this->_send_queue.end())
	{
		if(&((*its)->getConnection()) == connection)
		{
			delete *its;
			this->_send_queue.remove(*its);
			its = this->_send_queue.begin();
		}
		else
			its++;
	}

	// Remove Request use this connection pending in queue list.
	list<Request *>::iterator itr = this->_recv_queue.begin();
	while (itr != this->_recv_queue.end())
	{
		if(&((*itr)->getConnection()) == connection)
		{
			delete *itr;
			this->_recv_queue.remove(*itr);
			itr = this->_recv_queue.begin();
		}
		else
			itr++;
	}
	
	// Detete Connection
	this->_registred_connection.remove(connection);
	delete connection;
}

int			ConnectionManager::getMaxFd()
{
	int	max_fd = 1;

	for (list<Socket *>::iterator it = this->_registred_socket.begin(); it != this->_registred_socket.end(); it++)
		if (max_fd < (*it)->fd_socket)
			max_fd = (*it)->fd_socket;

	for (list<Connection *>::iterator it = this->_registred_connection.begin(); it != this->_registred_connection.end(); it++)
		if (max_fd < (*it)->_fd)
			max_fd = (*it)->_fd;
	
	return (max_fd);
}

Request		*ConnectionManager::NetworkActivitiesHandler()
{
	while (0 == 0)
	{
		struct timeval timeout;
		fd_set read_fds = this->_read_fds;
		fd_set write_fds = this->_write_fds;

		int select_status = 0;
		do
		{
			timeout.tv_sec = 0;
			timeout.tv_usec = 0;
			select_status = select(this->getMaxFd() + 1, &read_fds, &write_fds, NULL, NULL);

			if (_shutdown)
				return (NULL);
		} while (select_status == 0);

		if ( select_status < 0)
			Logging::SystemFatal("[Select]-Fd monitoring failed");
		
		// Check socket (incoming connection)
		for (list<Socket *>::iterator it = this->_registred_socket.begin(); it != this->_registred_socket.end(); it++)
		{
			if (FD_ISSET((*it)->fd_socket, &read_fds))
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
			if(FD_ISSET((*it)->getConnection()._fd, &write_fds))
			{
				Responce	*responce;

				cout << "[>]-(Server)-Send Messages." << endl;
				FD_CLR((*it)->getConnection()._fd, &this->_write_fds);
				responce = *it;
				responce->getConnection().sendResponce(*responce);

				this->_send_queue.remove(responce);
				if (responce->getDestroyConnection())
					this->removeConnection(&responce->getConnection());
				delete responce;
				
				it = this->_send_queue.begin();
				ite = this->_send_queue.end();
			}
			else
				it++;
		}

		// Check incoming Request (reading)
		for
		(
			list<Connection *>::iterator it = this->_registred_connection.begin();
			it != this->_registred_connection.end();
			it++
		)
		{
			if (FD_ISSET((*it)->_fd, &read_fds))
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
