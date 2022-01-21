//ERROR :KILLed by OperatorNickName: message
#include "Resources/Commands.hpp"

Responce *cmdKILL(Request	*request, command_context context)
{
	(void)context;
	(void)request;
	string	responsestr;

	string	message;
	string	ChanName;
	string	TargetName;
	string	reason;
	string	rest;

	if (request->getConnection().getClient().getIsOperator() == false)
	{
		responsestr = ":localhost 482 " + request->getConnection().getClient().getUserName() + " " + ChanName + " :Your privileges are too low\n";
		Responce *responce = new Responce(request->getConnection(), responsestr);
		return (responce);
	}

	message = request->getMessage();
	TargetName = message.substr(message.find_first_of(" \t")+1);
	reason = TargetName.substr(TargetName.find_first_of(" \t")+1);

	TargetName = TargetName.substr(0, TargetName.size()-(reason.length()));		

	TargetName = TargetName.substr(0, TargetName.size()-1);
	reason = reason.substr(0, reason.size()-2);

	list<Connection *>	connectionList;
	connectionList = context.connection_list->getConnectionList();
	list<Connection *>::iterator it;

	it = connectionList.begin();
	while (it != connectionList.end())
	{
		if ((*it)->getClient().getUserName() == TargetName)
		{
			responsestr = "ERROR :KILLed by " + request->getConnection().getClient().getUserName() + " " + reason +"\n";
			Responce *responce = new Responce((**it), responsestr, true);
			context.connection_list->addResponceToSendQueue(responce);
		}
		it++;
	}
	return (NULL);
}
