#include "Bot/Bot.hpp"

static	vector<string> joke_list;

int		better_random()
{
	ifstream	random_file;
	int			nombre = 0;

	random_file.open("/dev/random");
	random_file.read((char *)&nombre, sizeof(nombre));
	random_file.close();
	return (nombre);
}

void	BotCommands(command_context &context, Request *request, string &message)
{
	string command, args;
	message = message.erase(message.find_last_of('\n'));
	message = message.erase(message.find_last_of('\r'));

	command = message.substr(0 , message.find_first_of(" "));
	if (message.find_first_of(" ") != string::npos) 
		args = message.substr(message.find_first_of(" ")+1, message.size());

	cout << '\"' << command << '\"' << endl;
	cout << '\"' << args << '\"' << endl;

	if (command == "help")
		BotCommandHelp(context, request);
	else if (command == "user-list")
		BotCommandUserList(context, request);
	else if (command == "user-count")
		BotCommandUserCount(context, request);
	else if (command == "chanel-user-list")
		BotCommandChanelUserList(context, request, args);
	else if (command == "chanel-user-count")
		BotCommandChanelUserCount(context, request, args);
	else if (command == "tell-me-a-joke")
		BotCommandTellJoke(context, request);
	else if (command == "teach-me-a-joke")
		BotCommandLearnJoke(context, request, args);
	else
		BotSendMsg(context, request, "Hello I'am Tob the Bot type 'help' to get command list !");
}

// Commands
void	BotCommandHelp(command_context &context, Request *request)
{
	BotSendMsg(context, request, "Here is Tob user guide ! (My user guide) :");
	BotSendMsg(context, request, " - 'help' : Just what I told you.. Are you dumb?");
	BotSendMsg(context, request, " - 'user-count' : I'll show the number of user connected to server.");
	BotSendMsg(context, request, " - 'user-list' : I'll show a list username of user connected to server.");
	BotSendMsg(context, request, " - 'chanel-user-count $chan_name' : I'll show the number of user connected to a specific chanel.");
	BotSendMsg(context, request, " - 'chanel-user-list  $chan_name' : I'll show a list username of user connected to chanel.");
	BotSendMsg(context, request, " - 'tell-me-a-joke' : I'll just tell you good a joke.");
	BotSendMsg(context, request, " - 'teach-me-a-joke $the joke' : You can teach me a joke.");
}

void	BotCommandUserCount(command_context &context, Request *request)
{
	char buffer[16] = {0};

	sprintf(buffer, "%lu", context.connection_list->getConnectionList().size());

	BotSendMsg(
		context,
		request,
		string("There are currently ") + buffer + " users connected to the server."
	);
}

void	BotCommandUserList(command_context &context, Request *request)
{
	BotSendMsg(context, request, "List of user connected to the server :");

	list<Connection *>::iterator it = context.connection_list->getConnectionList().begin();
	while (it != context.connection_list->getConnectionList().end())
	{
		if ((*it)->getClient().getUserName().size() != 0)
			BotSendMsg(context, request, " - " + (*it)->getClient().getUserName());
		it++;
	}
}

void	BotCommandChanelUserCount(command_context &context, Request *request, string &chanelName)
{
	Chanel *chanel = NULL;

	if (context.chanels->find(chanelName) != context.chanels->end())
		chanel = &context.chanels->find(chanelName)->second;

	if (chanel && chanel->getPass().size() == 0)
	{
		char buffer[16] = {0};

		sprintf(buffer, "%lu", chanel->getMap().size());

		BotSendMsg(
			context,
			request,
			string("There are currently ") + buffer + " users connected to the chanel " + chanelName
		);
	}
	else
		BotSendMsg(
			context,
			request,
			string("Chanel ") + chanelName + " is private or dosen't exist." + chanelName
		);
}

void	BotCommandChanelUserList(command_context &context, Request *request, string &chanelName)
{
	Chanel *chanel = NULL;

	if (context.chanels->find(chanelName) != context.chanels->end())
		chanel = &context.chanels->find(chanelName)->second;

	if (chanel && chanel->getPass().size() == 0)
	{
		BotSendMsg(context, request, "List of user connected to the chanel " + chanelName + " :");

		map<Connection *, bool>::iterator it = chanel->getMap().begin();
		while (it != chanel->getMap().end())
		{
			if ((it->first)->getClient().getUserName().size() != 0)
				BotSendMsg(context, request, " - " + (it->first)->getClient().getUserName());
			it++;
		}
	}
	else
		BotSendMsg(
			context,
			request,
			string("Chanel ") + chanelName + " is private or dosen't exist." + chanelName
		);
}

void	BotCommandTellJoke(command_context &context, Request *request)
{
	if (joke_list.size() ==  0)
	{
		joke_list.push_back("I am not bot but real persone. Damn it, my nose...");
		joke_list.push_back("The best thing for notch is to have the cube head.");
		joke_list.push_back("Sorry but... I can't tell you this joke.");
		joke_list.push_back("I'm afraid for the calendar. Its days are numbered.");
		joke_list.push_back("My wife said I should do lunges to stay in shape. That would be a big step forward.");
		joke_list.push_back("Why do fathers take an extra pair of socks when they go golfing?" "In case they get a hole in one!");
		joke_list.push_back("Singing in the shower is fun until you get soap in your mouth. Then it's a soap opera.,");
		joke_list.push_back("What do a tick and the Eiffel Tower have in common?\" \"They're both Paris sites.");
	}

	
		BotSendMsg(context, request, joke_list[(unsigned long)(better_random() % joke_list.size())]);
}

void	BotCommandLearnJoke(command_context &context, Request *request, string &joke)
{
	if (joke.size() > 10)
		joke_list.push_back(joke);
	else
		BotSendMsg(context, request, "Are you kidding me?? Go and tell me a real joke I swear...");
}

// Utilities
void	BotSendMsg(command_context &context, Request *request, const string &messages)
{
	string messagesIrc = ":Tob!~Tob@localhost PRIVMSG " + request->getConnection().getClient().getUserName() + " :" + messages + "\n";
	context.connection_list->addResponceToSendQueue(new Responce(request->getConnection(), messagesIrc));
}