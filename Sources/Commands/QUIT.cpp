//QUIT
//ERROR :Closing connection

//QUIT test
//ERROR :"test"
#include "Resources/Commands.hpp"

Responce *cmdQUIT(Request	*request, command_context context)
{
	(void)context;
	string	responsestr;

	string	message;
	string	reason;

	message = request->getMessage();
	reason = message.substr(message.find_first_of(" \t")+1);
	reason = reason.substr(0, reason.size()-2);

	cout << "reason = " << reason << "TEST" << endl;

	if (reason.length() == 0)
	{
		responsestr = "ERROR :Closing connection\n";
		Responce *responce = new Responce(request->getConnection(), responsestr, true);
		return(responce);
	}
	else
	{
		responsestr = "ERROR :\"" + reason + "\"\n";
		Responce *responce = new Responce(request->getConnection(), responsestr, true);
		return(responce);
	}
	return (NULL);
}
