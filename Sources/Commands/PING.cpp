#include "Resources/Commands.hpp"

Responce *cmdPING(Request	*request, command_context context)
{
	(void)context;
	string responsestr;

	//:irc.example.net PONG irc.example.net :localhost
	responsestr = ":localhost PONG " + request->getConnection().getClient().getNickname() +  "\n";

	Responce *responce = new Responce(request->getConnection(), responsestr);
	return (responce);
}
