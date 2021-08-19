/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 16:35:46 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/19 19:20:17 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Message.hpp"
#include "Utilites/Networks/Connection.hpp"
class Connection;

class Request: public Message
{
	// Constructor & desctructor
	private:
		Request();
		Request(const Request &copy);
		Request &operator=(const Request &copy);
	public:
		Request(Connection &client, string message): Message(client, message) {}
		virtual ~Request()  {}
	
	// Setter Getter
	Connection			&getConnection() { return (this->_clientConnection); }
	virtual string		&getMessage() { return (this->_message); }
};
