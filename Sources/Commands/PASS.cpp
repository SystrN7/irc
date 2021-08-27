#include "Resources/Commands.hpp"

Responce *cmdPASS(Request	*request, command_context context)
{
	(void)context;
	string	responsestr;
	string	message;

	message = request->getMessage();
	string	Password = message.substr(message.find_first_of(" \t")+1);
	Password = Password.substr(0, Password.size()-2);

	if (Password == context.get)
	responsestr = ":localhost\\80 001 " + request->getConnection().getClient().getNickname() +  " :Nikname well set\n";

	Responce *responce = new Responce(request->getConnection(), responsestr);
	return (responce);
}
