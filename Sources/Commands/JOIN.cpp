#include "Resources/Commands.hpp"

// :irc.example.net 353 testuser2 = #test :testuser2 testuser @testuser3
// :irc.example.net 366 testuser2 #test :End of NAMES list

Responce *cmdJOIN(Request	*request, command_context context)
{
	string	responsestr;
	string	message;
	string	ChanName;
	string	Password;

	message = request->getMessage();
	ChanName = message.substr(message.find_first_of(" \t")+1);
	Password = ChanName.substr(ChanName.find_first_of(" \t")+1);
	ChanName = ChanName.substr(0, ChanName.size()-(Password.length()));	
	Password = Password.substr(0, Password.size()-2);

	if (ChanName.length() == 0)
		ChanName = Password;
	else
		ChanName = ChanName.substr(0, ChanName.size()-1);

	cout << "ChanName = " << ChanName << "TEST" << endl << "ChanPass = " << Password << "TEST" << endl << endl;

	if (ChanName.at(0) != '#')
	{
		responsestr = ":localhost\\80 403 " + request->getConnection().getClient().getNickname() +  " :No such nick/channel\n";
		Responce *responce = new Responce(request->getConnection(), responsestr);
		return (responce);
	}

	map<string, Chanel>::iterator it;
	it = context.chanels->find(ChanName);
	if (it != context.chanels->end())
	{
		//le chan existe
		cout << "Chan exists" << endl;
		if (it->second.getPass() == Password || (ChanName == Password && it->second.getPass().length() == 0))
		{
			//Le mdp est le bon
			cout << "Valid Password" << endl << endl;
			it->second.AddClient(&request->getConnection());
			responsestr = ":" + request->getConnection().getClient().getNickname() + "!~" + request->getConnection().getClient().getNickname() + "@localhost JOIN :" + ChanName + "\n";
		
			map<string, Chanel>::iterator it;
			map<Connection *, bool>::iterator it2;

			it = context.chanels->find(ChanName);
			if (it != context.chanels->end())
			{
				cout << it->first << endl;
				map<Connection *, bool>		map = it->second.getMap();
				it2 = map.begin();
				while (it2 != map.end())
				{
					if (&request->getConnection() != it2->first)
					{
						Responce *responce = new Responce(*it2->first, responsestr);
						context.connection_list->addResponceToSendQueue(responce);
					}
					it2++;
				}
			}
		}
		else
		{
			cout << "invalid password" << endl << endl;
			responsestr = ":localhost\\80 475 " + request->getConnection().getClient().getNickname() +  " :Cannot join channel (+k)\n";
		}
	}

	else
	{
		cout << "Chan must be created" << endl;
		//Il faut le créer (string name, Client *creator);
		if (Password != ChanName)
		{
			cout << "password set" << endl << endl;
			context.chanels->insert ( pair<string,Chanel>(ChanName, Chanel(ChanName, &(request->getConnection()), Password)) );
		}
		else
		{
			cout << "password NOT set" << endl << endl;
			context.chanels->insert ( pair<string,Chanel>(ChanName, Chanel(ChanName, &(request->getConnection())) ));
		}
		responsestr = ":" + request->getConnection().getClient().getNickname() + "!~" + request->getConnection().getClient().getNickname() + "@localhost JOIN :" + ChanName + "\n";
	}

	Responce *responce = new Responce(request->getConnection(), responsestr);
	return (responce);
}
