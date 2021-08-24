/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 17:52:45 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/24 14:54:51 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>

using namespace std;

typedef void (*CommandFunction)(void);

class Commands
{
	private:
		/* data */
		std::map	<string, CommandFunction>	_map; 

	public:
		Commands();
		~Commands();
};