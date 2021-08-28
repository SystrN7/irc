#include "Resources/Commands.hpp"

Responce *cmdOPER(Request	*request, command_context context)
{
	(void)context;
	string	responsestr;
	string	truepass ("444667");
	string	message;
	string	trypass;

	message = request->getMessage();
	trypass = message.substr(message.find_first_of(" \t")+1);
	trypass = trypass.substr(trypass.find_first_of(" \t")+1);
	trypass = trypass.substr(0, trypass.size()-2);

	if (trypass == truepass)
	{
		responsestr = ":localhost 381 " + request->getConnection().getClient().getNickname() +  " :You are now an IRC operator\n";
		request->getConnection().getClient().setIsOperator(true);
	}
	else
		responsestr = ":localhost 481 " + request->getConnection().getClient().getNickname() +  " :Permission Denied- You're not an IRC operator\n";
	Responce *responce = new Responce(request->getConnection(), responsestr);
	return (responce);
}
