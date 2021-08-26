/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:03:11 by seruiz            #+#    #+#             */
/*   Updated: 2021/08/26 11:59:56 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Resources/Chanel.hpp"

Chanel::Chanel (string name, Client *creator) : _ChanName(name)
{
	this->_map.insert (std::pair<Client *,bool>(creator, true)); //Le createur d'un chan y est forcement op
}

Chanel::Chanel (string name, Client *creator, string pass) : _ChanName(name), _ChanPass(pass)
{
	this->_map.insert (std::pair<Client *,bool>(creator, true)); //Le createur d'un chan y est forcement op
}


Chanel::~Chanel()
{ }

void	Chanel::AddClient(Client *NewClient)
{
	this->_map.insert (std::pair<Client *,bool>(NewClient, NewClient->getIsOperator()));
}

void	Chanel::RemoveClient(Client *RemovedClient) 
{
	this->_map.erase(RemovedClient);
}

void	Chanel::AddOpRole(Client *NewOp)
{
	std::map<Client *, bool>::iterator it;
	it = this->_map.find(NewOp);

	if (it != this->_map.end())
		it->second = true;
}

void	Chanel::RemoveOpRole(Client *RemoveOp)
{
	std::map<Client *, bool>::iterator it;
	it = this->_map.find(RemoveOp);

	if (it != this->_map.end())
		it->second = false;
}