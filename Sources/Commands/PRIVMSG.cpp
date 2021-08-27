//PRIVMSG ServName/UserName :Message
//:irc.example.net 401 testuser #test :No such nick or channel name

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
		map<Connection *, bool>::iterator itIsIn;
		it = context.chanels->find(ChanName);
		if (it != context.chanels->end())
		{
			map<Connection *, bool>		map = it->second.getMap();
			itIsIn = map.find(&request->getConnection());
			if (itIsIn != map.end())
			{
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
			else
			{
				responsestr = ":localhost\\80 401 " + request->getConnection().getClient().getNickname() + " " + ChanName + " :No such nick or channel name\n";
				Responce *responce = new Responce(request->getConnection(), responsestr);
				return (responce);
			}
		}
	}
	return (NULL);
}