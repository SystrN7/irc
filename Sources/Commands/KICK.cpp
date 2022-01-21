//KICK #test testuser2 reason
//Commande envoyée à tout les membres du chan
//:testuser!~testuser@localhost KICK #test testuser2 :reason

// :irc.example.net 482 testuser2 #test :Your privileges are too low

#include "Resources/Commands.hpp"

Responce *cmdKICK(Request	*request, command_context context)
{
	(void)context;
	(void)request;
	string	responsestr;

	string	message;
	string	ChanName;
	string	TargetName;
	string	rest;

	message = request->getMessage();
	ChanName = message.substr(message.find_first_of(" \t")+1);
	TargetName = ChanName.substr(ChanName.find_first_of(" \t")+1);
	ChanName = ChanName.substr(0, ChanName.size()-(TargetName.length()));	
	rest = TargetName.substr(TargetName.find_first_of(" \t")+1);
	TargetName = TargetName.substr(0, TargetName.size()-(rest.length()));	
	rest = rest.substr(0, rest.size()-2);

	ChanName = ChanName.substr(0, ChanName.size()-1);
	TargetName = TargetName.substr(0, TargetName.size()-1);

	if (TargetName.length() == 0 || ChanName.length() == 0 || rest.length() == 0)
		return (NULL);

	map<string, Chanel>::iterator it;
	map<Connection *, bool>::iterator it2;
	map<Connection *, bool>::iterator itIsIn;
	it = context.chanels->find(ChanName);
	if (it != context.chanels->end())
	{
		map<Connection *, bool>		map = it->second.getMap();
		itIsIn = map.find(&request->getConnection());
		if (itIsIn != map.end())
		{
			if (request->getConnection().getClient().getIsOperator() == true || itIsIn->second == true)
			{
				it2 = map.begin();
				while (it2 != map.end())
				{
					if (it2->first->getClient().getUserName() == TargetName)
						it->second.RemoveClient(it2->first);
					responsestr = ":" + request->getConnection().getClient().getUserName() + "!~" + request->getConnection().getClient().getNickname() + "@localhost KICK " + ChanName + " " + TargetName + " " + rest + "\n";
					Responce *responce = new Responce(*it2->first, responsestr);
					context.connection_list->addResponceToSendQueue(responce);
					it2++;
				}
			}
			else
			{
				responsestr = ":localhost 482 " + request->getConnection().getClient().getUserName() + " " + ChanName + " :Your privileges are too low\n";
				Responce *responce = new Responce(request->getConnection(), responsestr);
				return (responce);
			}
		}
		else
		{
			responsestr = ":localhost 401 " + request->getConnection().getClient().getUserName() + " " + ChanName + " :No such nick or channel name\n";
			Responce *responce = new Responce(request->getConnection(), responsestr);
			return (responce);
		}
	}
	return (NULL);
}
