#include "Resources/Commands.hpp"

Responce *cmdPING(Request	*request, command_context context)
{
	(void)context;
	string responsestr;

	responsestr = ":localhost\\80 PONG " + request->getConnection().getClient().getNickname() +  "\n";

	Responce *responce = new Responce(request->getConnection(), responsestr);
	return (responce);
}
