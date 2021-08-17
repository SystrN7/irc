/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 14:48:40 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/17 15:05:03 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <sstream>

#include "Core/ConnectionManager.hpp"

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
