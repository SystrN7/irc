/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 14:48:40 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/25 11:23:16 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <csignal>
#include <string>
#include <iostream>
#include <sstream>

#include "Core/ConnectionManager.hpp"

using namespace std;

class Core
{
	/* Attribute */
	public:
		static bool			_shutdown;
	private:
		ConnectionManager	_connection_manager;
		int					_port_number;
		string				_password;

	/* Constructor & Destructor */
	private:
		Core();
	public:
		Core(const string port, const string password, const string existing_network = "");
		void parsingParams(const string port, const string password, const string existing_network);
		void showHeader();
		void start();
		~Core();
	
	/* Operator */

	/* Getter */

	/* Setter */

	/* Methode */
	
};

// Function to close server
void	shutdown_server(int code);
