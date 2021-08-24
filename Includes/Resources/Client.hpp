/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 17:52:45 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/24 10:01:20 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

using namespace std;

class Client
{
	private:
		/* data */
		string	_nick;
		bool	_isOperator;
	public:
		Client();
		Client(string name);
		Client(string name, bool isop);
		Client(bool isop);
		~Client();

		bool	getIsOperator();
};