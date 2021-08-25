/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 14:48:40 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/25 11:56:55 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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

	/* Constructor & Destructor */
	private:
		Core();
	public:
		Core(const string port, const string password, const string existing_network = "");
		~Core();
	
	/* Operator */

	/* Getter */

	/* Setter */

	/* Methode */
	
};
