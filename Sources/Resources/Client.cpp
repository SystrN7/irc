/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:03:23 by seruiz            #+#    #+#             */
/*   Updated: 2021/08/25 14:37:08 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Resources/Client.hpp"

Client::Client() : _nick("user"), _isOperator(false) {};

Client::Client(bool isop) : _nick("user"), _isOperator(isop) {};

Client::Client(string name) : _nick(name), _isOperator(false) {};

Client::Client(string name, bool isop) : _nick(name), _isOperator(isop) {};

Client::Client(string name, bool isop, Chanel *chanel) : _nick(name), _isOperator(isop), _chanel(chanel) {};

bool	Client::getIsOperator(){return (this->_isOperator);};

void	Client::setIsOperator(bool isop){this->_isOperator = isop; };

Client::~Client() {};

string	Client::getNickname(){ return (this->_nick); };

void	Client::setNickname(string NewName) { this->_nick = NewName; };