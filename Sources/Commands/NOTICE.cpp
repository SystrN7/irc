// notice testuser2 test
// NOTICE testuser2 :wesh
//:testuser!~testuser@localhost NOTICE testuser2 :wesh

#include "Resources/Commands.hpp"

Responce *cmdNOTICE(Request	*request, command_context context)
{
	(void)context;
	(void)request;
	string	responsestr;

	string	message;
	string	SentMessage;
	string	TargetName;
	string	rest;

	message = request->getMessage();
	TargetName = message.substr(message.find_first_of(" \t")+1);
	rest = TargetName.substr(TargetName.find_first_of(" \t")+1);
	TargetName = TargetName.substr(0, TargetName.size()-(rest.length()));	
	rest = rest.substr(0, rest.size()-2);
	TargetName = TargetName.substr(0, TargetName.size()-1);
	
	SentMessage = message.substr(message.find_first_of(" \t")+1);

	if (TargetName.length() == 0 || SentMessage.length() == 0 || rest.length() == 0)
		return (NULL);

	if (TargetName.at(0) != '#')
	{
		responsestr = ":" + request->getConnection().getClient().getUserName() + "!~" + request->getConnection().getClient().getUserName() + "@localhost NOTICE " + TargetName + " " + rest + "\n";
		
		list<Connection *>	connectionList = context.connection_list->getConnectionList();
		list<Connection *>::iterator itusr = connectionList.begin();
		while (itusr != connectionList.end())
		{
			if ((*itusr)->getClient().getUserName() == TargetName)
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
		it = context.chanels->find(TargetName);
		if (it != context.chanels->end())
		{
			map<Connection *, bool>		map = it->second.getMap();
			cout << "Context map size = " << map.size() << endl;
			itIsIn = map.find(&request->getConnection());
			if (itIsIn != map.end())
			{
				it2 = map.begin();
				while (it2 != map.end())
				{
					if (&request->getConnection() != it2->first)
					{
						responsestr = ":" + request->getConnection().getClient().getUserName() + "!~" + request->getConnection().getClient().getUserName() + "@localhost NOTICE " + TargetName + " " + rest + "\n";
						Responce *responce = new Responce(*it2->first, responsestr);
						context.connection_list->addResponceToSendQueue(responce);
					}
					it2++;
				}
			}
			else
			{
				responsestr = ":localhost 401 " + request->getConnection().getClient().getUserName() + " " + TargetName + " :No such nick or channel name\n";
				Responce *responce = new Responce(request->getConnection(), responsestr);
				return (responce);
			}
		}
	}
	return (NULL);
}