/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 11:23:50 by seruiz            #+#    #+#             */
/*   Updated: 2021/08/25 12:21:34 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Resources/Commands.hpp"

Commands::Commands()
{ }

Commands::~Commands()
{ }

Responce	*Commands::ExecCommand(Request *request)
{
	Client		&_client = request->getConnection().getClient();
	(void)_client;
	string		message = request->getMessage();

	string 		CommandName = message.substr(0, message.find(" "));
	
	std::cout << "Command Name = " << CommandName << std::endl;


	Responce *test = new Responce(request->getConnection(), string(":localhost\\80 001 fgalaup :Welcome to the Internet Relay Chat\n"));
	return (test);
}
