/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 16:35:46 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/27 14:39:07 by seruiz           ###   ########lyon.fr   */
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
		bool		_destroyConnection;
	public:
		Responce(Connection &client, string message): Message(client, message), _destroyConnection(false){}
		Responce(Connection &client, string message, bool destroy): Message(client, message), _destroyConnection(destroy){}
		virtual ~Responce() {}
	
	// Setter Getter
	Connection			&getConnection() { return (this->_clientConnection); }
	virtual string		&getMessage() { return (this->_message); }
	bool				getDestroyConnection() { return (this->_destroyConnection); }
	void				setDestroyConnection(bool destroy) { this->_destroyConnection = destroy; }
};