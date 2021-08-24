/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:03:04 by seruiz            #+#    #+#             */
/*   Updated: 2021/08/24 12:01:53 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include <string>
#include <map>

using namespace std;

class Chanel
{
	private:
		/* data */
		std::map	<Client *, bool>	_map; 
		string							_ChanName;

	public:
		Chanel();
		Chanel (string name, Client *creator);
		~Chanel();

		void	AddClient(Client *NewClient);
		void	RemoveClient(Client *RemovedClient);
		void	AddOpRole(Client *NewOp);
		void	RemoveOpRole(Client *RemoveOp);
};