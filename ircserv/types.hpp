#pragma once
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <string>
#include <ctime>
#include <exception>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class IrcLog;
class Socket;
class Server;
class Command;
class User;
class Channel;
class Messanger;

typedef enum {
	ERR_NOSUCHNICK			= 401,
	ERR_NOSUCHCHANNEL		= 403,
	ERR_CANNOTSENDTOCHAN	= 404,
	ERR_TOOMANYCHANNELS		= 405,
	ERR_ERRONEUSNICKNAME	= 432,
	ERR_NICKNAMEINUSE		= 433,
	ERR_USERNOTINCHANNEL	= 441,
	ERR_NOTONCHANNEL		= 442,
	ERR_NOTREGISTERED		= 451,
	ERR_NEEDMOREPARAMS		= 461,
	ERR_NOPERMFORHOST		= 463,
	ERR_PASSWDMISMATCH		= 464,
	ERR_CHANNELISFULL		= 471,
	ERR_UNKNOWNMODE			= 472,
	ERR_INVITEONLYCHAN		= 473,
	ERR_BANNEDFROMCHAN		= 474,
	ERR_BADCHANNELKEY		= 475,
	ERR_BADCHANMASK			= 476,
	ERR_CHANOPRIVSNEEDED 	= 482,
	ERR_USERSDONTMATCH		= 502,
	ERR_INVALIDPARAM		= 695,
	ERR_SPECIFYPARAM		= 696,
	ERR_ALREADYBANNED		= 697,
	ERR_ISNOTBANNED			= 698,
}	t_err;

typedef enum {
	RPL_UMODEIS			= 221,
	RPL_WHOISUSER		= 311,
	RPL_WHOISSERVER		= 312,
	RPL_ENDOFWHO		= 315,
	RPL_WHOISIDLE		= 317,
	RPL_ENDOFWHOIS		= 318,
	RPL_LISTSTART		= 321,
	RPL_LIST			= 322,
	RPL_LISTEND			= 323,
	RPL_CHANNELMODEIS	= 324,
	RPL_TIMESTAMP		= 329,
	RPL_TOPIC			= 332,
	RPL_TOPICTIME		= 333,
	RPL_INVITING		= 341,
	RPL_WHOREPLY		= 352,
	RPL_NAMREPLY		= 353,
	RPL_ENDOFNAMES		= 366,
	RPL_BANLIST			= 367,
	RPL_ENDOFBANLIST	= 368,
	RPL_HOSTNAME		= 378,
	RPL_USERMODES		= 379,
}	t_rpl;

typedef struct s_param {
	string channel_name;
	Channel *channel;
	string user_name;
	User *user;
	string comment;
	int indicator;
	int match_idx;
	char mode;
	string syntax;
	IrcLog *log;
	bool flag;
}	param_t;

typedef struct s_mode {
	char mode;
	string param;
}	channel_mode_t;

string ulToString(size_t num);
