/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 14:52:50 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/19 15:27:49 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Core/ConnectionManager.hpp"

ConnectionManager::ConnectionManager(void):
	_registred_socket(),
	_registred_connection(),
	_read_fds(),
	_write_fds(),
	_read_fd_count(0),
	_write_fd_count(0)
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
	this->_read_fd_count = 0;
	for (list<Socket *>::iterator it = this->_registred_socket.begin(); it != this->_registred_socket.end(); it++)
	{
		FD_SET((*it)->fd_socket, &this->_read_fds);
		this->_read_fd_count++;
	}
}

void	ConnectionManager::monitorConnection()
{
	// Wait full request befor reading bloking durring reading (wait end file signal)

	// Wait availability befor writing to avoid bloking durring writing
}

#include <iostream>
#include <fstream>
#include <sstream>

void		ConnectionManager::monitorFileDescriptor()
{
	this->monitorSocket();

		ifstream ifs("./messges.irc");
		string content( (istreambuf_iterator<char>(ifs) ),
				(istreambuf_iterator<char>()));

	while (0 == 0)
	{
		if (select(FD_SETSIZE, &this->_read_fds, &this->_write_fds, NULL, NULL) <= 0)
			Logging::SystemFatal("[Select]-Fd monitoring failed");
		
		// Check socket 
		for (list<Socket *>::iterator it = this->_registred_socket.begin(); it != this->_registred_socket.end(); it++)
		{
			cout << "Socket" << endl;
			if (FD_ISSET((*it)->fd_socket, &this->_read_fds))
			{
				cout << "[+]-[Connection](Client)-New client request." << endl;
				Connection	*connection = (*it)->getConnection();
				this->registerConnection(connection);
				FD_SET(connection->_fd, &this->_read_fds);
				// FD_SET(connection->_fd, &this->_write_fds);
			}
		}
		cout << "test" << endl;
		// Check Connection reading / writing
		for (list<Connection *>::iterator it = this->_registred_connection.begin(); it != this->_registred_connection.end(); it++)
		{
			cout << "Connection" << endl;
			// Reading
			if (FD_ISSET((*it)->_fd, &this->_read_fds))
			{
				cout << "[<]-(Client)-Recive Data" << endl;
				cout << *(*it)->receiveData() << endl;
				// Writing
				// if(FD_ISSET((*it)->_fd, &this->_write_fds))
				// {
					cout << "[>]-(Client)-Send Data." << endl;
					cout << "Send: " << content << endl;
					cout << "size of : " << content.size() << endl;
					(*it)->sendData(content.c_str() , content.size());
					// FD_SET((*it)->_fd, &this->_read_fds);
					// // FD_SET((*it)->_fd, &this->_write_fds);
					// FD_CLR((*it)->_fd, &this->_write_fds);
					// FD_CLR((*it)->_fd, &this->_read_fds);

					// delete (*it);
					// this->_registred_connection.remove(*it);
					// it = this->_registred_connection.begin();
				// }
			}
			
		}

		// this->monitorSocket();
		// this->monitorConnection();
	}
}
