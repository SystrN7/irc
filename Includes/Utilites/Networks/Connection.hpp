/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:47:10 by fgalaup           #+#    #+#             */
/*   Updated: 2021/08/19 17:31:46 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Core/Logging.hpp"

#include "Resources/Request.hpp"
#include "Resources/Responce.hpp"

#include <unistd.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include <string>

using namespace std;

class Connection
{
	private:
		int						_fd;
		struct sockaddr_in		_client_address;

	private:
		Connection(void);
		Connection(const Connection &rhs);
		Connection			&operator=(const Connection &rhs);
		

	public:
		Connection(int fd, struct sockaddr_in address);
		~Connection(void);

		void	printInfo();
		Request *receiveRequest();
		int	sendResponce(Responce &message);
	
	friend class ConnectionManager;
};