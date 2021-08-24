#pragma once

#include <string>
#include <map>
#include "Client.hpp"

using namespace std;

class Chanel
{
	private:
		/* data */
		std::map	<Client, bool>		_map; 
		std::map<Client,bool>::iterator _it;
		string							_ChanName;

	public:
		Chanel();
		Chanel (string name, Client &creator);
		~Chanel();

		void	AddClient(Client &NewClient);
		void	RemoveClient(Client &RemovedClient);
		void	AddOpRole(Client &NewOp);
		void	RemoveOpRole(Client &RemoveOp);
};