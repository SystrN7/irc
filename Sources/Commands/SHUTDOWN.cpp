#include "Resources/Commands.hpp"
#include "IRC.hpp"

Responce *cmdSHUTDOWN(Request	*request, command_context context)
{
	(void)context;
	string	responsestr;

	if (request->getConnection().getClient().getIsOperator())
		_shutdown = true;
	else
	{
		responsestr = ":localhost 482 " + request->getConnection().getClient().getUserName() + " :Your privileges are too low\n";
		Responce *responce = new Responce(request->getConnection(), responsestr);
		return (responce);
	}
	return (NULL);
}
