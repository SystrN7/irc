/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 17:52:45 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/25 12:20:54 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include "Request.hpp"
#include "Responce.hpp"

using namespace std;

typedef void (*CommandFunction)(void);

class Commands
{
	private:
		/* data */
		// std::map	<string, CommandFunction>	_map; 
		// Request		*_request;

	public:
		Commands	();
		virtual		~Commands();//delet la request dans le destructeur maybe

		Responce	*ExecCommand(Request *request);
};