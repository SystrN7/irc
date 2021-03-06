/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 17:52:45 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/28 12:55:54 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

using namespace std;

class Chanel;

class Client
{
	private:
		Client(Client &rhs);
		Client(const Client &rhs);
		Client	&operator=(const Client &rhs);
		/* data */
		string	_nick;
		string	_user;
		bool	_isOperator;
		bool	_isIdentified;
		// Chanel	*_chanel;
	public:
		Client();
		Client(string name);
		Client(string name, bool isop);
		Client(bool isop);
		//Client(string name, bool isop, Chanel *chanel);
		~Client();

		// Chanel	*getChanel() {return (this->_chanel);};
		bool	getIsOperator();
		void	setIsOperator(bool isop);
		string	getNickname();
		void	setNickname(string NewName);
		string	getUserName();
		void	setUserName(string NewUserName);
		void	setIsIdentified(bool isId);
		bool	getIsIdentified(void);	
};