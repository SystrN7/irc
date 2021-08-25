#include "Resources/Commands.hpp"

Responce *cmdOPER(Request	*request, command_context context)
{
	(void)context;
	string responsestr;
	string pass ("444667");
	string	message;

	message = request->getMessage();
	string	NickName = message.substr(message.find_first_of(" \t")+1);
	NickName = NickName.substr(0, NickName.size()-1);

	std::size_t found = message.find(pass);
	if (found!=std::string::npos)
	{
		responsestr = ":localhost\\80 381 " + request->getConnection().getClient().getNickname() +  " :You are now an IRC operator\n";
		request->getConnection().getClient().setIsOperator(true);
	}
	else
		responsestr = ":localhost\\80 481 " + request->getConnection().getClient().getNickname() +  " :Permission Denied- You're not an IRC operator\n";

	Responce *responce = new Responce(request->getConnection(), responsestr);
	return (responce);
}
