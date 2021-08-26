#include "Resources/Commands.hpp"

Responce *cmdJOIN(Request	*request, command_context context)
{
	string	responsestr;

	string	message;
	string	ChanName;
	string	Password;

	message = request->getMessage();
	ChanName = message.substr(message.find_first_of(" \t")+1);

	Password = ChanName.substr(ChanName.find_first_of(" \t")+1);
	// if (!Password.empty())
	// 	cout << "there is a password";

	
	ChanName = ChanName.substr(0, ChanName.size()-(Password.length()));	

	Password = Password.substr(0, Password.size()-2);

	if (ChanName.length() == 0)
		ChanName = Password;
	else
		ChanName = ChanName.substr(0, ChanName.size()-1);
	/*
	if (ChanName == Password)
		ChanName = ChanName.substr(0, ChanName.size()-2);
	else
	{
		cout << "WESH" << endl;
		ChanName = ChanName.substr(0, ChanName.size()-(Password.length() + 3));	
	}
	*/

	//cout << "ChanName = " << ChanName << endl << "PassWord = " << Password << endl << endl;

	//Essaye de chercher si le chan Existe dans la liste et essayer de s'y connecter
	//Sinon, crée le chan avec ou sans mdp

	cout << "ChanName = " << ChanName << "TEST" << endl << "ChanPass = " << Password << "TEST" << endl << endl;

	if (ChanName.at(0) != '#')
	{
		responsestr = ":localhost\\80 403 " + request->getConnection().getClient().getNickname() +  " :No such nick/channel\n";
		Responce *responce = new Responce(request->getConnection(), responsestr);
		return (responce);
	}

	map<string, Chanel>::iterator it2;
	it2 = context.chanels->begin();
	while (it2 != context.chanels->end())
	{
		cout << it2->first << endl;
		it2++;
	}
	cout << endl;

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
			//responsestr.append (":irc.example.net 353 " + request->getConnection().getClient().getNickname() + " = " + ChanName + ":@" + request->getConnection().getClient().getNickname() + "\n");
			//responsestr.append (":irc.example.net 366 " + request->getConnection().getClient().getNickname() + " " + ChanName + ":End of NAMES list" + "\n");
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
		//responsestr.append (":irc.example.net 353 " + request->getConnection().getClient().getNickname() + " = " + ChanName + ":@" + request->getConnection().getClient().getNickname() + "\n");
		//responsestr.append (":irc.example.net 366 " + request->getConnection().getClient().getNickname() + " " + ChanName + ":End of NAMES list" + "\n");
	}

	Responce *responce = new Responce(request->getConnection(), responsestr);
	return (responce);
}
