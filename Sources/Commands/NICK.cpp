#include "Resources/Commands.hpp"

Responce *cmdNICK(Request	*request, command_context context)
{
	(void)context;
	string	responsestr;
	string	message;

	message = request->getMessage();
	string	NickName = message.substr(message.find_first_of(" \t")+1);
	NickName = NickName.substr(0, NickName.size()-2);

	responsestr = ":" + request->getConnection().getClient().getNickname() +  "!~" + request->getConnection().getClient().getNickname() + "@localhost NICK :" + NickName + "\n";
	request->getConnection().getClient().setNickname(NickName);

	Responce *responce = new Responce(request->getConnection(), responsestr);
	return (responce);
}
