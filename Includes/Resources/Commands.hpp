/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 17:52:45 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/25 16:34:38 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include "Request.hpp"
#include "Responce.hpp"
#include "Core/ConnectionManager.hpp"
#include "Chanel.hpp"
using namespace std;

typedef struct	s_command_context
{
	ConnectionManager			*connection_list;
	map<string, Chanel>			*chanels;
}				command_context;

typedef Responce *(*CommandFunction)(Request *request, command_context);

Responce	*cmdNICK(Request	*request, command_context context);
Responce	*cmdUSER(Request	*request, command_context context);
Responce	*cmdOPER(Request	*request, command_context context);
Responce	*cmdPING(Request	*request, command_context context);

class Commands
{
	/* data */
	private:
		map<string, CommandFunction>	_commands_list;
		command_context					_context;
	public:
		Commands	();
		virtual		~Commands();
		void		addCommand(string command_name, CommandFunction);
		void		setContext(command_context context) { this->_context = context; }
		Responce	*ExecCommand(Request *request);
};
