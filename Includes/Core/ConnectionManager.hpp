/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 14:52:47 by fgalaup           #+#    #+#             */
/*   Updated: 2021/07/23 11:45:59 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Utilites/Networks/Socket.hpp"
#include "Utilites/Networks/Connection.hpp"

#include <list>
#include <iostream>
#include <sys/select.h>

using namespace std;

class ConnectionManager
{
		private:
				list<Socket *>		_registred_socket;
				list<Connection *>	_registred_connection;
				fd_set				_read_fds;
				fd_set				_write_fds;
				unsigned int		_read_fd_count;
				unsigned int		_write_fd_count;
		private:
				ConnectionManager(const ConnectionManager &rhs);
				ConnectionManager		&operator=(const ConnectionManager &rhs);
		public:
				ConnectionManager(void);
				virtual ~ConnectionManager(void);

				void	registerSocket(Socket *socket);
				void	registerConnection(Connection *connection);
				void	monitorFileDescriptor();

		private :
				void	monitorSocket();
				void	monitorConnection();
};
