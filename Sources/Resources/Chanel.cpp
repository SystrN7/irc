/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:03:11 by seruiz            #+#    #+#             */
/*   Updated: 2021/08/28 12:30:13 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Resources/Chanel.hpp"

Chanel::Chanel (string name, Connection *connection) : _ChanName(name)
{
	this->AddClient(connection);
	this->_map[connection] = true;
	//this->_map.insert (std::pair<Connection *,bool>(connection, true)); //Le createur d'un chan y est forcement op
}

Chanel::Chanel (string name, Connection *creator, string pass) : _ChanName(name), _ChanPass(pass)
{
	this->AddClient(creator);
	this->_map[creator] = true;
	//this->_map.insert (std::pair<Connection *,bool>(creator, true)); //Le createur d'un chan y est forcement op
}


Chanel::~Chanel()
{ }

void	Chanel::AddClient(Connection *NewConnection)
{
	map<Connection *, bool>::iterator it = this->_map.begin();

	cout << "Before add " << endl;
	while (it != this->_map.end())
	{
		cout << it->first->getClient().getNickname() << endl;
		it++;
	}

	this->_map.insert (std::pair<Connection *,bool>(NewConnection, NewConnection->getClient().getIsOperator()));
	NewConnection->registerChanel(this);

	it = this->_map.begin();
	cout << "After  add " <<endl;
	while (it != this->_map.end())
	{
		cout << it->first->getClient().getNickname() << endl;
		it++;
	}
	cout <<endl;
}

void	Chanel::RemoveClient(Connection *RemovedClient) 
{
	map<Connection *, bool>::iterator it = this->_map.begin();

	cout << "Before remove " << endl;
	while (it != this->_map.end())
	{
		cout << it->first->getClient().getNickname() << endl;
		it++;
	}

	this->_map.erase(RemovedClient);
	RemovedClient->unregisterChanel(this);

	it = this->_map.begin();
	cout << "After  remove " << endl;
	while (it != this->_map.end())
	{
		cout << it->first->getClient().getNickname() << endl;
		it++;
	}
	cout <<endl;

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