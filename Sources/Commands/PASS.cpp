///location : Users/seruiz/.config/weechat/irc.conf
//change default password

#include "Resources/Commands.hpp"

Responce *cmdPASS(Request	*request, command_context context)
{
	(void)context;
	string	responsestr;
	string	message;

	message = request->getMessage();
	string	Password = message.substr(message.find_first_of(" \t")+1);
	Password = Password.substr(0, Password.size()-2);

	if (request->getConnection().getClient().getIsIdentified() == true || request->getConnection().getClient().getUserName().length() != 0)
	{
		responsestr = ":localhost 462 " + request->getConnection().getClient().getUserName() + " :Connection already registered\n";
		Responce *responce = new Responce(request->getConnection(), responsestr);
		return (responce);
	}
	if (Password == context.ServPass || context.ServPass.length() == 0)
		request->getConnection().getClient().setIsIdentified(true);
	else
		request->getConnection().getClient().setIsIdentified(false);
	return (NULL);
}
