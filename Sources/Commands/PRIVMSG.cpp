//PRIVMSG ServName/UserName :Message

#include "Resources/Commands.hpp"

Responce *cmdPRIVMSG(Request	*request, command_context context)
{
	(void)context;
	(void)request;
	string	responsestr;

	string	message;
	string	SentMessage;
	string	ChanName;
	string	rest;

	message = request->getMessage();
	ChanName = message.substr(message.find_first_of(" \t")+1);
	rest = ChanName.substr(ChanName.find_first_of(" \t")+1);
	ChanName = ChanName.substr(0, ChanName.size()-(rest.length()));	
	rest = rest.substr(0, rest.size()-2);
	ChanName = ChanName.substr(0, ChanName.size()-1);
	
	SentMessage = message.substr(message.find_first_of(" \t")+1);

	if (ChanName.at(0) != '#')
	{
		responsestr = ":" + request->getConnection().getClient().getNickname() + "!~" + request->getConnection().getClient().getNickname() + "@localhost PRIVMSG " + SentMessage + "\n";
		
		list<Connection *>	connectionList = context.connection_list->getConnectionList();
		list<Connection *>::iterator itusr = connectionList.begin();
		while (itusr != connectionList.end())
		{
			if ((*itusr)->getClient().getNickname() == ChanName)
			{
				Responce *responce = new Responce(**itusr, responsestr);
				return (responce);
			}
			itusr++;
		}
	}

	else
	{
		map<string, Chanel>::iterator it;
		map<Connection *, bool>::iterator it2;
		it = context.chanels->find(ChanName);
		if (it != context.chanels->end())
		{
			cout << it->first << endl;
			map<Connection *, bool>		map = it->second.getMap();
			it2 = map.begin();
			while (it2 != map.end())
			{
				if (&request->getConnection() != it2->first)
				{
					responsestr = ":" + request->getConnection().getClient().getNickname() + "!~" + request->getConnection().getClient().getNickname() + "@localhost PRIVMSG " + SentMessage + "\n";
					Responce *responce = new Responce(*it2->first, responsestr);
					context.connection_list->addResponceToSendQueue(responce);
				}
				it2++;
			}
		}
	}
	return (NULL);
}