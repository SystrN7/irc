/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logging.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:19:35 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/17 15:07:00 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Core/Logging.hpp"

void Logging::Fatal(const char *message, int return_code)
{
	cerr << "[\033[31m*\033[0m] - " << message << endl;
	exit(return_code);
}

void Logging::Error(const char *message)
{
	cerr << "[\033[31mx\033[0m] - " << message << endl;
}

void Logging::Warning(const char *message)
{
	cerr << "[\033[33m!\033[0m] - " << message << endl;
}

void Logging::Info(const char *message)
{
	cout << "[\033[94mi\033[0m] - " << message << endl;
}

void Logging::Debug(const char *message)
{
	if (DEBUG)
		cout << "[\033[97m#\033[0m] - " << message << endl;
}
