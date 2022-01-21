#include "Resources/Commands.hpp"

//ERROR :Access denied: Bad password?

bool	usernameExist(list<Connection *> &connection_list, string &username);

Responce *cmdUSER(Request	*request, command_context context)
{
	(void)context;
	string	responsestr;
	string	username;
	string	rest;
	string	message;

	message = request->getMessage();
	username = message.substr(message.find_first_of(" \t")+1);
	rest = username.substr(username.find_first_of(" \t")+1);
	username = username.substr(0, username.size()-(rest.length()));	
	rest = rest.substr(0, rest.size()-2);
	username = username.substr(0, username.size()-1);

	if (username.length() == 0 || rest.length() == 0)
		return (NULL);

	if (context.ServPass.length() == 0)
		request->getConnection().getClient().setIsIdentified(true);

	if (request->getConnection().getClient().getIsIdentified() == false && request->getConnection().getClient().getUserName().length() == 0)
	{	
		responsestr = "ERROR :Access denied: Bad password?\n";
		Responce *responce = new Responce(request->getConnection(), responsestr, true);
		return (responce);
	}
	else if
	(
		request->getConnection().getClient().getUserName().length() == 0 &&
		username == request->getConnection().getClient().getNickname() &&
		!usernameExist(context.connection_list->getConnectionList(), username)
	)
	{
		request->getConnection().getClient().setUserName(username);
		responsestr = ":localhost 001 " + request->getConnection().getClient().getUserName() +  " :Welcome to the Internet Relay Network " + request->getConnection().getClient().getNickname() + "!\n";
		BotSendMsg(context, request, "Hello i'am the Tob bot you cant interact with me. To get list of interaction type 'help'.");
	}
	else
		responsestr = ":localhost 462 " + request->getConnection().getClient().getNickname() + " :Connection already registered\n";


	Responce *responce = new Responce(request->getConnection(), responsestr);
	return (responce);
}

bool	usernameExist(list<Connection *> &connection_list, string &username)
{
	list<Connection *>::iterator it = connection_list.begin();
	while (it != connection_list.end())
	{
		if ((*it)->getClient().getUserName() == username)
			return (true);
		it++;
	}
	
	return (false);
}
