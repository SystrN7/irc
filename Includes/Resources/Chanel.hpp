/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:03:04 by seruiz            #+#    #+#             */
/*   Updated: 2021/08/26 16:22:47 by seruiz           ###   ########lyon.fr   */
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
};