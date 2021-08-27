/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 11:23:50 by seruiz            #+#    #+#             */
/*   Updated: 2021/08/27 15:48:49 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Resources/Commands.hpp"
Commands::Commands()
{ }
Commands::~Commands()
{ }
void		Commands::addCommand(string command_name, CommandFunction function)
{
	if (function)
		this->_commands_list[command_name] = function;
}

Responce	*Commands::ExecCommand(Request *request)
{
	string		message = request->getMessage();
	string		command_name = message.substr(0, message.find(" "));

	if (command_name == message)
		command_name = command_name.substr(0, command_name.size()-2);
	map<string, CommandFunction>::iterator it = this->_commands_list.find(command_name);
	if (it == this->_commands_list.end())
	{
		cout << "NULL" << endl;
		return (NULL);
	}
	return (it->second(request, this->_context));
}