/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logging.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:19:35 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/17 15:59:28 by fgalaup          ###   ########lyon.fr   */
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

// System Error

void Logging::SystemFatal(const char *message, int return_code)
{
	cerr << "[\033[31m*\033[0m] - " << message << " : " << strerror(errno) << endl;
	exit(return_code);
}

void Logging::SystemError(const char *message)
{
	cerr << "[\033[31mx\033[0m] - " << message << " : " << strerror(errno) << endl;
}

void Logging::SystemWarning(const char *message)
{
	cerr << "[\033[33m!\033[0m] - " << message << " : " << strerror(errno) << endl;
}

void Logging::SystemInfo(const char *message)
{
	cout << "[\033[94mi\033[0m] - " << message << " : " << strerror(errno) << endl;
}