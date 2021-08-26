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

	if (TargetName.at(0) != '#')
	{
		responsestr = ":" + request->getConnection().getClient().getNickname() + "!~" + request->getConnection().getClient().getNickname() + "@localhost NOTICE " + TargetName + " " + rest + "\n";
		
		list<Connection *>	connectionList = context.connection_list->getConnectionList();
		list<Connection *>::iterator itusr = connectionList.begin();
		while (itusr != connectionList.end())
		{
			if ((*itusr)->getClient().getNickname() == TargetName)
			{
				Responce *responce = new Responce(**itusr, responsestr);
				return (responce);
			}
			itusr++;
		}
	}
	return (NULL);
}