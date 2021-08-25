/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 16:35:09 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/25 10:53:39 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

// #include "Utilites/Networks/Connection.hpp"

using namespace std;

class Connection;

class Message
{
	protected:
		Connection	&_clientConnection;
		string		_message;
	
	// Constructor & desctructor
	private:
		Message();
		Message(const Message &copy);
		Message &operator=(const Message &copy);
	public:
		Message(Connection &client, string message);
		virtual ~Message();
	
	// Setter Getter
	Connection	&getConnection() { return (this->_clientConnection); }
	string		&getMessage() { return (this->_message); }
};
