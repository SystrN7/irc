#pragma once

#include <cstdlib>

#include <fstream>
#include <string>
#include <list>
#include <vector>

#include "Resources/Chanel.hpp"
#include "Resources/Commands.hpp"
#include "Resources/Request.hpp"
#include "Resources/Responce.hpp"
#include "Resources/Commands.hpp"

using namespace std;

void	BotSendMsg(command_context &context, Request *request, const string &messages);
void	BotCommands(command_context &context, Request *request, string &command);

void	BotCommandHelp(command_context &context, Request *request);
void	BotCommandUserCount(command_context &context, Request *request);
void	BotCommandUserList(command_context &context, Request *request);
void	BotCommandChanelUserList(command_context &context, Request *request, string &chanelName);
void	BotCommandChanelUserCount(command_context &context, Request *request, string &chanelName);
void	BotCommandTellJoke(command_context &context, Request *request);
void	BotCommandLearnJoke(command_context &context, Request *request, string &joke);
