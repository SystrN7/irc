/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 14:52:47 by fgalaup           #+#    #+#             */
/*   Updated: 2022/01/10 15:48:14 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"
#include "Utilites/Networks/Socket.hpp"
#include "Utilites/Networks/Connection.hpp"

#include "Resources/Request.hpp"
#include "Resources/Responce.hpp"

#include <list>
#include <iostream>
#include <sys/select.h>

using namespace std;

class ConnectionManager
{
		private:
				list<Socket *>		_registred_socket;
				list<Connection *>	_registred_connection;
				list<Responce *>	_send_queue;
				list<Request *>		_recv_queue;
				fd_set				_read_fds;
				fd_set				_write_fds;
		private:
				ConnectionManager(const ConnectionManager &rhs);
				ConnectionManager		&operator=(const ConnectionManager &rhs);
				int		getMaxFd();
		public:
				ConnectionManager(void);
				virtual ~ConnectionManager(void);
				void	registerSocket(Socket *socket);
				void	registerConnection(Connection *connection);
				void	removeConnection(Connection *connection);
				void	addResponceToSendQueue(Responce *responce);
				Request	*NetworkActivitiesHandler();
				list<Connection *> &getConnectionList() { return (this->_registred_connection); };
};
