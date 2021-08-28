///part #channelname
//Cmd envoyée à tout les membres du chan :
//:testuser2!~testuser2@localhost PART #test :

#include "Resources/Commands.hpp"

Responce *cmdPART(Request	*request, command_context context)
{
	string	responsestr;
	string	message;
	string	ChanName;
	string	rest;

	message = request->getMessage();
	ChanName = message.substr(message.find_first_of(" \t")+1);
	rest = ChanName.substr(ChanName.find_first_of(" \t")+1);
	ChanName = ChanName.substr(0, ChanName.size()-(rest.length()));	
	rest = rest.substr(0, rest.size()-2);
	ChanName = ChanName.substr(0, ChanName.size()-1);

	if (ChanName.length() == 0 || rest.length() == 0)
		return (NULL);

	if (ChanName.at(0) != '#')
	{
		responsestr = ":localhost 403 " + request->getConnection().getClient().getNickname() +  " :No such nick/channel\n";
		Responce *responce = new Responce(request->getConnection(), responsestr);
		return (responce);
	}

	map<string, Chanel>::iterator it;
	it = context.chanels->find(ChanName);
	if (it != context.chanels->end())
	{
		responsestr = ":" + request->getConnection().getClient().getNickname() + "!~" + request->getConnection().getClient().getNickname() + "@localhost PART " + ChanName + " :\n";
		map<string, Chanel>::iterator it;
		map<Connection *, bool>::iterator it2;
		it = context.chanels->find(ChanName);
		if (it != context.chanels->end())
		{
			map<Connection *, bool>		map = it->second.getMap();
			it2 = map.begin();
			while (it2 != map.end())
			{
				if (&request->getConnection() == it2->first)
				{
					it->second.RemoveClient(&request->getConnection());
				}
				else
				{
					Responce *responce = new Responce(*it2->first, responsestr);
					context.connection_list->addResponceToSendQueue(responce);
				}
				it2++;
			}
		}
		else
			responsestr = ":localhost 403 " + request->getConnection().getClient().getNickname() +  " :No such nick/channel\n";
	}

	Responce *responce = new Responce(request->getConnection(), responsestr);
	return (responce);
}
