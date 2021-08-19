/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 14:52:47 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/19 19:13:08 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
				list<Responce *>	_sendQueue;
				fd_set				_read_fds;
				fd_set				_write_fds;
		private:
				ConnectionManager(const ConnectionManager &rhs);
				ConnectionManager		&operator=(const ConnectionManager &rhs);
		public:
				ConnectionManager(void);
				virtual ~ConnectionManager(void);
				void	registerSocket(Socket *socket);
				void	monitorSocket();
				void	registerConnection(Connection *connection);
				void	addResponceToSendQueue(Responce *responce);
				Request	*NetworkActivitiesHandler();
};
