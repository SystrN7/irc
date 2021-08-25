#include "Resources/Commands.hpp"

Responce *cmdNICK(Request	*request, command_context context)
{
	(void)context;
	string	responsestr;
	string	message;

	message = request->getMessage();
	string	NickName = message.substr(message.find_first_of(" \t")+1);
	NickName = NickName.substr(0, NickName.size()-1);
	request->getConnection().getClient().setNickname(NickName);

	responsestr = ":localhost\\80 001 " + request->getConnection().getClient().getNickname() +  " :Nikname well set\n";

	Responce *responce = new Responce(request->getConnection(), responsestr);
	return (responce);
}
