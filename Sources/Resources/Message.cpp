/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 17:04:27 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/19 17:57:32 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Resources/Message.hpp"

Message::Message(Connection &client, string message):
	_clientConnection(client),
	_message(message)
{ }

Message::~Message()
{ }
