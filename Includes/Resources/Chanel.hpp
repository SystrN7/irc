/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:03:04 by seruiz            #+#    #+#             */
/*   Updated: 2021/08/27 15:56:46 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// #include "Client.hpp"
#include "Utilites/Networks/Connection.hpp"
#include <string>
#include <map>

using namespace std;

class Connection;

class Chanel
{
	private:
		/* data */
		std::map	<Connection *, bool>	_map;
		string								_ChanName;
		string								_ChanPass;

	private:
		// Chanel(const Chanel &rhs);
		// Chanel		&operator=(const Chanel &rhs);
	public:
		Chanel();
		Chanel (string name, Connection *connection);
		Chanel (string name, Connection *connection, string pass);
		~Chanel();

		void	AddClient(Connection *NewConnection);
		void	RemoveClient(Connection *RemovedConnection);
		void	AddOpRole(Connection *NewOp);
		void	RemoveOpRole(Connection *RemoveOp);
		string	getPass() { return(this->_ChanPass); }
		std::map	<Connection *, bool> &getMap() { return(this->_map); }
};