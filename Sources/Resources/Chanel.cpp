/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:03:11 by seruiz            #+#    #+#             */
/*   Updated: 2021/08/26 16:18:23 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Resources/Chanel.hpp"

Chanel::Chanel (string name, Connection *connection) : _ChanName(name)
{
	this->_map.insert (std::pair<Connection *,bool>(connection, true)); //Le createur d'un chan y est forcement op
}

Chanel::Chanel (string name, Connection *creator, string pass) : _ChanName(name), _ChanPass(pass)
{
	this->_map.insert (std::pair<Connection *,bool>(creator, true)); //Le createur d'un chan y est forcement op
}


Chanel::~Chanel()
{ }

void	Chanel::AddClient(Connection *NewConnection)
{
	this->_map.insert (std::pair<Connection *,bool>(NewConnection, NewConnection->getClient().getIsOperator()));
}

void	Chanel::RemoveClient(Connection *RemovedClient) 
{
	this->_map.erase(RemovedClient);
}

void	Chanel::AddOpRole(Connection *NewOp)
{
	std::map<Connection *, bool>::iterator it;
	it = this->_map.find(NewOp);

	if (it != this->_map.end())
		it->second = true;
}

void	Chanel::RemoveOpRole(Connection *RemoveOp)
{
	std::map<Connection *, bool>::iterator it;
	it = this->_map.find(RemoveOp);

	if (it != this->_map.end())
		it->second = false;
}