/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logging.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:19:45 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/17 16:49:25 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRC.hpp"

#include <cerrno>
#include <cstdlib>
#include <cstring>

#include <iostream>

using namespace std;

class Logging
{
	private:
		Logging(Logging const &ref);
		Logging &operator=(Logging const &ref);
	public:
		virtual ~Logging();
	
	// System Error

	static void SystemFatal(const char *message, int exit_code = 1);
	static void SystemError(const char *message);
	static void SystemWarning(const char *message);
	static void SystemInfo(const char *message);

	// Common Error

	static void Fatal(const char *message, int exit_code = 1);
	static void Error(const char *message);
	static void Warning(const char *message);
	static void Info(const char *message);
	static void Debug(const char *message);
};