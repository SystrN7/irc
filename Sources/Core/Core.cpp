/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:55:20 by seruiz            #+#    #+#             */
/*   Updated: 2021/08/27 14:04:42 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Core/Core.hpp"

bool _shutdown;

/**
 * Valid Program inputs
 * [host:port_network:password_network] <port> <password>
 * 
 *  - host: is the hostname on which IRC must connect to join a already existing network.
 *  - port_network: is the server port on which IRC must connect on host.
 *  - password_network: is the password needed to connect on host.
 * 
 *  - port: is the port number on which your server will accept incoming connections.
 *  - password: is the password needed by any IRC client who wants to connect to your server.
 * 
 * If host,port_network and password_network aren't given, you must create a new IRC network.
 */
int main(int argc, char const *argv[])
{
	if (argc > 4 || argc < 3)
		Logging::Fatal("Wrong number of arguments.");
	if (argc == 4)
		Logging::Fatal("Join an other network is not supported.");
	Core ServerCore(argv[1], argv[2]);
	ServerCore.start();
	return (0);
}


Core::Core(const string port, const string password, const string existing_network)
{
	_shutdown = false;
	this->parsingParams(port, password, existing_network);
}

void	Core::showHeader()
{
	cout << "\033[38;2;240;20;122m [39m[38;2;238;18;126m_[39m[38;2;236;16;130m_[39m[38;2;234;14;135m_[39m[38;2;231;12;139m_[39m[38;2;229;11;143m_[39m[38;2;226;9;147m [39m[38;2;224;8;151m_[39m[38;2;221;6;156m_[39m[38;2;218;5;160m_[39m[38;2;215;4;164m_[39m[38;2;212;3;168m_[39m[38;2;208;2;172m [39m[38;2;205;2;176m [39m[38;2;202;1;180m [39m[38;2;198;1;183m_[39m[38;2;195;1;187m_[39m[38;2;191;1;191m_[39m[38;2;187;1;195m_[39m[38;2;184;1;198m_[39m[38;2;180;1;202m [39m[38;2;176;2;205m [39m[38;2;172;2;208m_[39m[38;2;168;3;211m_[39m[38;2;164;4;215m_[39m[38;2;160;5;218m_[39m[38;2;156;6;221m_[39m[38;2;152;7;223m [39m[38;2;147;9;226m [39m[38;2;143;10;229m [39m[38;2;139;12;231m [39m[38;2;135;14;234m [39m[38;2;131;16;236m [39m[38;2;126;18;238m [39m[38;2;122;20;240m [39m[38;2;118;23;242m [39m[38;2;114;25;244m [39m[38;2;110;28;245m [39m[38;2;105;30;247m [39m[38;2;101;33;248m [39m[38;2;97;36;249m [39m[38;2;93;39;251m [39m[38;2;89;42;252m [39m[38;2;85;45;252m [39m[38;2;81;48;253m [39m[38;2;77;52;254m [39m[38;2;73;55;254m [39m[38;2;69;59;254m [39m[38;2;66;62;254m [39m[38;2;62;66;254m [39m[38;2;58;70;254m [39m[38;2;55;74;254m [39m[38;2;51;77;254m [39m[38;2;48;81;253m[39m " << endl;
	cout << "\033[38;2;234;14;135m|[39m[38;2;231;12;139m_[39m[38;2;229;11;143m [39m[38;2;226;9;147m [39m[38;2;224;8;151m [39m[38;2;221;6;156m_[39m[38;2;218;5;160m|[39m[38;2;215;4;164m [39m[38;2;212;3;168m [39m[38;2;208;2;172m_[39m[38;2;205;2;176m_[39m[38;2;202;1;180m [39m[38;2;198;1;183m\\[39m[38;2;195;1;187m [39m[38;2;191;1;191m/[39m[38;2;187;1;195m [39m[38;2;184;1;198m_[39m[38;2;180;1;202m_[39m[38;2;176;2;205m_[39m[38;2;172;2;208m_[39m[38;2;168;3;211m|[39m[38;2;164;4;215m/[39m[38;2;160;5;218m [39m[38;2;156;6;221m_[39m[38;2;152;7;223m_[39m[38;2;147;9;226m_[39m[38;2;143;10;229m_[39m[38;2;139;12;231m|[39m[38;2;135;14;234m [39m[38;2;131;16;236m [39m[38;2;126;18;238m [39m[38;2;122;20;240m [39m[38;2;118;23;242m [39m[38;2;114;25;244m [39m[38;2;110;28;245m [39m[38;2;105;30;247m [39m[38;2;101;33;248m [39m[38;2;97;36;249m [39m[38;2;93;39;251m [39m[38;2;89;42;252m [39m[38;2;85;45;252m [39m[38;2;81;48;253m [39m[38;2;77;52;254m [39m[38;2;73;55;254m [39m[38;2;69;59;254m [39m[38;2;66;62;254m [39m[38;2;62;66;254m [39m[38;2;58;70;254m [39m[38;2;55;74;254m [39m[38;2;51;77;254m [39m[38;2;48;81;253m [39m[38;2;45;85;252m [39m[38;2;42;89;251m [39m[38;2;39;93;251m[39m " << endl;
	cout << "\033[38;2;226;9;147m [39m[38;2;224;8;151m [39m[38;2;221;6;156m|[39m[38;2;218;5;160m [39m[38;2;215;4;164m|[39m[38;2;212;3;168m [39m[38;2;208;2;172m|[39m[38;2;205;2;176m [39m[38;2;202;1;180m|[39m[38;2;198;1;183m_[39m[38;2;195;1;187m_[39m[38;2;191;1;191m)[39m[38;2;187;1;195m [39m[38;2;184;1;198m|[39m[38;2;180;1;202m [39m[38;2;176;2;205m|[39m[38;2;172;2;208m [39m[38;2;168;3;211m [39m[38;2;164;4;215m [39m[38;2;160;5;218m [39m[38;2;156;6;221m|[39m[38;2;152;7;223m [39m[38;2;147;9;226m([39m[38;2;143;10;229m_[39m[38;2;139;12;231m_[39m[38;2;135;14;234m_[39m[38;2;131;16;236m [39m[38;2;126;18;238m [39m[38;2;122;20;240m [39m[38;2;118;23;242m_[39m[38;2;114;25;244m_[39m[38;2;110;28;245m_[39m[38;2;105;30;247m [39m[38;2;101;33;248m_[39m[38;2;97;36;249m [39m[38;2;93;39;251m_[39m[38;2;89;42;252m_[39m[38;2;85;45;252m_[39m[38;2;81;48;253m_[39m[38;2;77;52;254m [39m[38;2;73;55;254m [39m[38;2;69;59;254m [39m[38;2;66;62;254m_[39m[38;2;62;66;254m_[39m[38;2;58;70;254m_[39m[38;2;55;74;254m_[39m[38;2;51;77;254m_[39m[38;2;48;81;253m [39m[38;2;45;85;252m_[39m[38;2;42;89;251m [39m[38;2;39;93;251m_[39m[38;2;36;97;249m_[39m[38;2;33;102;248m [39m[38;2;30;106;247m[39m " << endl;
	cout << "\033[38;2;218;5;160m [39m[38;2;215;4;164m [39m[38;2;212;3;168m|[39m[38;2;208;2;172m [39m[38;2;205;2;176m|[39m[38;2;202;1;180m [39m[38;2;198;1;183m|[39m[38;2;195;1;187m [39m[38;2;191;1;191m [39m[38;2;187;1;195m_[39m[38;2;184;1;198m [39m[38;2;180;1;202m [39m[38;2;176;2;205m/[39m[38;2;172;2;208m|[39m[38;2;168;3;211m [39m[38;2;164;4;215m|[39m[38;2;160;5;218m [39m[38;2;156;6;221m [39m[38;2;152;7;223m [39m[38;2;147;9;226m [39m[38;2;143;10;229m [39m[38;2;139;12;231m\\[39m[38;2;135;14;234m_[39m[38;2;131;16;236m_[39m[38;2;126;18;238m_[39m[38;2;122;20;240m [39m[38;2;118;23;242m\\[39m[38;2;114;25;244m [39m[38;2;110;28;245m/[39m[38;2;105;30;247m [39m[38;2;101;33;248m_[39m[38;2;97;36;249m [39m[38;2;93;39;251m\\[39m[38;2;89;42;252m [39m[38;2;85;45;252m'[39m[38;2;81;48;253m_[39m[38;2;77;52;254m_[39m[38;2;73;55;254m\\[39m[38;2;69;59;254m [39m[38;2;66;62;254m\\[39m[38;2;62;66;254m [39m[38;2;58;70;254m/[39m[38;2;55;74;254m [39m[38;2;51;77;254m/[39m[38;2;48;81;253m [39m[38;2;45;85;252m_[39m[38;2;42;89;251m [39m[38;2;39;93;251m\\[39m[38;2;36;97;249m [39m[38;2;33;102;248m'[39m[38;2;30;106;247m_[39m[38;2;27;110;245m_[39m[38;2;25;114;244m|[39m[38;2;22;118;242m[39m " << endl;
	cout << "\033[38;2;208;2;172m [39m[38;2;205;2;176m_[39m[38;2;202;1;180m|[39m[38;2;198;1;183m [39m[38;2;195;1;187m|[39m[38;2;191;1;191m_[39m[38;2;187;1;195m|[39m[38;2;184;1;198m [39m[38;2;180;1;202m|[39m[38;2;176;2;205m [39m[38;2;172;2;208m\\[39m[38;2;168;3;211m [39m[38;2;164;4;215m\\[39m[38;2;160;5;218m|[39m[38;2;156;6;221m [39m[38;2;152;7;223m|[39m[38;2;147;9;226m_[39m[38;2;143;10;229m_[39m[38;2;139;12;231m_[39m[38;2;135;14;234m_[39m[38;2;131;16;236m [39m[38;2;126;18;238m_[39m[38;2;122;20;240m_[39m[38;2;118;23;242m_[39m[38;2;114;25;244m_[39m[38;2;110;28;245m)[39m[38;2;105;30;247m [39m[38;2;101;33;248m|[39m[38;2;97;36;249m [39m[38;2;93;39;251m [39m[38;2;89;42;252m_[39m[38;2;85;45;252m_[39m[38;2;81;48;253m/[39m[38;2;77;52;254m [39m[38;2;73;55;254m|[39m[38;2;69;59;254m [39m[38;2;66;62;254m [39m[38;2;62;66;254m [39m[38;2;58;70;254m\\[39m[38;2;55;74;254m [39m[38;2;51;77;254mV[39m[38;2;48;81;253m [39m[38;2;45;85;252m/[39m[38;2;42;89;251m [39m[38;2;39;93;251m [39m[38;2;36;97;249m_[39m[38;2;33;102;248m_[39m[38;2;30;106;247m/[39m[38;2;27;110;245m [39m[38;2;25;114;244m|[39m[38;2;22;118;242m [39m[38;2;20;123;240m [39m[38;2;18;127;238m [39m[38;2;16;131;236m[39m " << endl;
	cout << "\033[38;2;198;1;183m|[39m[38;2;195;1;187m_[39m[38;2;191;1;191m_[39m[38;2;187;1;195m_[39m[38;2;184;1;198m_[39m[38;2;180;1;202m_[39m[38;2;176;2;205m|[39m[38;2;172;2;208m_[39m[38;2;168;3;211m|[39m[38;2;164;4;215m [39m[38;2;160;5;218m [39m[38;2;156;6;221m\\[39m[38;2;152;7;223m_[39m[38;2;147;9;226m\\[39m[38;2;143;10;229m\\[39m[38;2;139;12;231m_[39m[38;2;135;14;234m_[39m[38;2;131;16;236m_[39m[38;2;126;18;238m_[39m[38;2;122;20;240m_[39m[38;2;118;23;242m|[39m[38;2;114;25;244m_[39m[38;2;110;28;245m_[39m[38;2;105;30;247m_[39m[38;2;101;33;248m_[39m[38;2;97;36;249m_[39m[38;2;93;39;251m/[39m[38;2;89;42;252m [39m[38;2;85;45;252m\\[39m[38;2;81;48;253m_[39m[38;2;77;52;254m_[39m[38;2;73;55;254m_[39m[38;2;69;59;254m|[39m[38;2;66;62;254m_[39m[38;2;62;66;254m|[39m[38;2;58;70;254m [39m[38;2;55;74;254m [39m[38;2;51;77;254m [39m[38;2;48;81;253m [39m[38;2;45;85;252m\\[39m[38;2;42;89;251m_[39m[38;2;39;93;251m/[39m[38;2;36;97;249m [39m[38;2;33;102;248m\\[39m[38;2;30;106;247m_[39m[38;2;27;110;245m_[39m[38;2;25;114;244m_[39m[38;2;22;118;242m|[39m[38;2;20;123;240m_[39m[38;2;18;127;238m|[39m[38;2;16;131;236m [39m[38;2;14;135;233m [39m[38;2;12;140;231m [39m[38;2;10;144;228m[39m " << endl;
	cout << "\033[38;2;187;1;195m [39m[38;2;184;1;198m [39m[38;2;180;1;202m [39m[38;2;176;2;205m [39m[38;2;172;2;208m [39m[38;2;168;3;211m [39m[38;2;164;4;215m [39m[38;2;160;5;218m [39m[38;2;156;6;221m [39m[38;2;152;7;223m [39m[38;2;147;9;226m [39m[38;2;143;10;229m [39m[38;2;139;12;231m [39m[38;2;135;14;234m [39m[38;2;131;16;236m [39m[38;2;126;18;238m [39m[38;2;122;20;240m [39m[38;2;118;23;242m [39m[38;2;114;25;244m [39m[38;2;110;28;245m [39m[38;2;105;30;247m [39m[38;2;101;33;248m [39m[38;2;97;36;249m [39m[38;2;93;39;251m [39m[38;2;89;42;252m [39m[38;2;85;45;252m [39m[38;2;81;48;253m [39m[38;2;77;52;254m [39m[38;2;73;55;254m [39m[38;2;69;59;254m [39m[38;2;66;62;254m [39m[38;2;62;66;254m [39m[38;2;58;70;254m [39m[38;2;55;74;254m [39m[38;2;51;77;254m [39m[38;2;48;81;253m [39m[38;2;45;85;252m [39m[38;2;42;89;251m [39m[38;2;39;93;251m [39m[38;2;36;97;249m [39m[38;2;33;102;248m [39m[38;2;30;106;247m [39m[38;2;27;110;245m [39m[38;2;25;114;244m [39m[38;2;22;118;242m [39m[38;2;20;123;240m [39m[38;2;18;127;238m [39m[38;2;16;131;236m [39m[38;2;14;135;233m [39m[38;2;12;140;231m [39m[38;2;10;144;228m [39m[38;2;9;148;226m [39m[38;2;7;152;223m [39m[38;2;6;156;220m[39m "  << endl;
}
void	Core::parsingParams(const string port, const string password, const string existing_network)
{
	//====Checking parameter====//
	(void)existing_network;

	// Check port number
	stringstream stream;

	stream << port;
	stream >> this->_port_number;

	if (this->_port_number < 1 || this->_port_number > 65535)
		Logging::Fatal("The port number is invalid it must be between 1 and 65535 !");

	this->_password = password;
	// Check password
	if (password.length() < 5 && password.length() > 42)
		Logging::Fatal("The password must contain at least 5 characters long and least than 42 characters !");
}

void	Core::registerCommands()
{
	this->_command_runner.addCommand("LIST", NULL);
	this->_command_runner.addCommand("USER", cmdUSER);
	this->_command_runner.addCommand("NICK", cmdNICK);
	this->_command_runner.addCommand("PING", cmdPING);
	this->_command_runner.addCommand("PONG", NULL);
	this->_command_runner.addCommand("QUIT", NULL);
	this->_command_runner.addCommand("PASS", cmdPASS);
	this->_command_runner.addCommand("SERVER", NULL);
	this->_command_runner.addCommand("SQUIT", NULL);
	this->_command_runner.addCommand("CONNECT", NULL);
	this->_command_runner.addCommand("OPER", cmdOPER);
	this->_command_runner.addCommand("ERROR", NULL);
	this->_command_runner.addCommand("ADMIN", NULL);
	this->_command_runner.addCommand("MOTD", NULL);
	this->_command_runner.addCommand("USERHOST", NULL);
	this->_command_runner.addCommand("VERSION", NULL);
	this->_command_runner.addCommand("INFO", NULL);
	this->_command_runner.addCommand("TIME", NULL);
	this->_command_runner.addCommand("JOIN", cmdJOIN);
	this->_command_runner.addCommand("PRIVMSG", cmdPRIVMSG);
	this->_command_runner.addCommand("INVITE", NULL);
	this->_command_runner.addCommand("NAMES", NULL);
	this->_command_runner.addCommand("WHO", NULL);
	this->_command_runner.addCommand("WHOIS", NULL);
	this->_command_runner.addCommand("WHOWAS", NULL);
	this->_command_runner.addCommand("PART", cmdPART);
	this->_command_runner.addCommand("MODE", NULL);
	this->_command_runner.addCommand("NOTICE", cmdNOTICE);
	this->_command_runner.addCommand("AWAY", NULL);
	this->_command_runner.addCommand("KILL", NULL);
	this->_command_runner.addCommand("LINKS", NULL);
	this->_command_runner.addCommand("STATS", NULL);
	this->_command_runner.addCommand("NJOIN", NULL);
	this->_command_runner.addCommand("LUSERS", NULL);
	this->_command_runner.addCommand("ISON", NULL);	
	this->_command_runner.addCommand("USERS", NULL);
	this->_command_runner.addCommand("TOPIC", NULL);
	this->_command_runner.addCommand("KICK", cmdKICK);
	this->_command_runner.addCommand("TRACE", NULL);
	this->_command_runner.addCommand("DIE", NULL);
	this->_command_runner.addCommand("WALLOPS", NULL);
	this->_command_runner.addCommand("REHASH", NULL);
	this->_command_runner.addCommand("SERVICE", NULL);
	this->_command_runner.addCommand("SERVLIST", NULL);
	this->_command_runner.addCommand("SQUERY", NULL);
}

void	Core::start()
{
	command_context	context;

	this->showHeader();
	this->registerCommands();
	signal(SIGINT, &shutdown_server);
	Socket*	socket = new Socket(this->_port_number);
	this->_connection_manager.registerSocket(socket);

	// this->_chanels["index"] = Chanel();
	
	context.chanels = &this->_chanels;
	context.connection_list = &this->_connection_manager;
	context.ServPass = this->_password;
	this->_command_runner.setContext(context);

	Logging::Info("server is ready. waiting client request !");

	while (7 == 7)
	{
		Request *request = this->_connection_manager.NetworkActivitiesHandler();
		if (request)
		{
			cout << "Recive :" << request->getMessage() << endl;
			Responce 	*responce;
			responce = 	this->_command_runner.ExecCommand(request);
			if (responce)
				this->_connection_manager.addResponceToSendQueue(responce);
			delete request;
		}
		// shutdown server
		if (_shutdown)
			break;
	}
}

Core::~Core()
{
	
}

void	shutdown_server(int code)
{
	(void)code;
	_shutdown = true;
}