#include "Resources/Commands.hpp"

//ERROR :Access denied: Bad password?

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
	else if (request->getConnection().getClient().getUserName().length() == 0)
	{
		responsestr = ":localhost 001 " + request->getConnection().getClient().getNickname() +  " :Welcome to the Internet Relay Network " + request->getConnection().getClient().getNickname() + "!\n";
		request->getConnection().getClient().setUserName(username);
	}
	else
		responsestr = ":localhost 462 " + request->getConnection().getClient().getNickname() + " :Connection already registered\n";

	Responce *responce = new Responce(request->getConnection(), responsestr);
	return (responce);
}
