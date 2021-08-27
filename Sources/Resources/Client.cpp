/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:03:23 by seruiz            #+#    #+#             */
/*   Updated: 2021/08/27 10:42:15 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Resources/Client.hpp"

Client::Client() : _nick("user"), _user(""), _isOperator(false) {}

Client::Client(bool isop) : _nick("user"), _user(""), _isOperator(isop) {}

Client::Client(string name) : _nick(name), _user(""), _isOperator(false) {}

Client::Client(string name, bool isop) : _nick(name), _user(""), _isOperator(isop) {}

//Client::Client(string name, bool isop, Chanel *chanel) : _nick(name), _isOperator(isop), _chanel(chanel) {};

bool	Client::getIsOperator(){return (this->_isOperator);}

void	Client::setIsOperator(bool isop){this->_isOperator = isop; }

Client::~Client() {};

string	Client::getNickname(){ return (this->_nick); }

void	Client::setNickname(string NewName) { this->_nick = NewName; }

string	Client::getUserName() { return(this->_user); }

void	Client::setUserName(string NewUserName) { this->_user = NewUserName; }