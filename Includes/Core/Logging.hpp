/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logging.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:19:45 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/13 15:27:37 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

#include <cstdlib>

#include <iostream>

using namespace std;

class Logging
{
	private:
		Logging(Logging const &ref);
		Logging &operator=(Logging const &ref);
	public:
		virtual ~Logging();
	
	static void Fatal(const char *message, int exit_code = 1);
	static void Error(const char *message);
	static void Warning(const char *message);
	static void Info(const char *message);
	static void Debug(const char *message);
};