/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 14:48:40 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/27 11:41:46 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"

#include <csignal>
#include <string>
#include <iostream>
#include <sstream>

#include "Core/ConnectionManager.hpp"
#include "Resources/Commands.hpp"

using namespace std;

class Core
{
    /* Attribute */
    private:
        map<string, Chanel>	_chanels;
        Commands			_command_runner;
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
        void registerCommands();
        void start();
        ~Core();

    /* Operator */

    /* Getter */

    /* Setter */

    /* Methode */

};

// Function to close server
void	shutdown_server(int code);
