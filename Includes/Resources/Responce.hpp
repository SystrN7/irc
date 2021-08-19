/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 16:35:46 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/19 19:19:41 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Message.hpp"
#include "Utilites/Networks/Connection.hpp"
class Connection;

class Responce: public Message
{
	// Constructor & desctructor
	private:
		Responce();
		Responce(const Responce &copy);
		Responce &operator=(const Responce &copy);
	public:
		Responce(Connection &client, string message): Message(client, message) {}
		virtual ~Responce() {}
	
	// Setter Getter
	Connection			&getConnection() { return (this->_clientConnection); }
	virtual string		&getMessage() { return (this->_message); }
};