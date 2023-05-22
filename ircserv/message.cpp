#include "ircserv.hpp"

void checkError(Server &serv, User *sender, t_err err_no, param_t param) {
	switch (err_no) {
		case ERR_NOSUCHNICK:
			if (!param.user) {
				sender->stringAdd(":" + serv.getServName() + " 401 " + sender->getNickname()
					+ " " + param.user_name + " :No such nick");
				throw exception();
			}
			break;

		case ERR_NOSUCHCHANNEL:
			if (!param.channel) {
				sender->stringAdd(":" + serv.getServName() + " 403 " + sender->getNickname()
					+ " " + param.channel_name + " :No such channel");
				throw exception();
			}
			break;

		case ERR_CANNOTSENDTOCHAN:
			if (param.mode == 'm' && !param.channel->isOperUser(sender) && !param.channel->hasVoice(sender)) {
				sender->stringAdd(":" + serv.getServName() + " 404 " + sender->getNickname()
					+ " " + param.channel_name + " :You cannot send messages to this channel whilst the +m (moderated) mode is set.");
				throw exception();
			} else if (param.mode == 'b' && !param.channel->isOperUser(sender) && param.channel->isBanned(sender)) {
				sender->stringAdd(":" + serv.getServName() + " 404 " + sender->getNickname()
					+ " " + param.channel_name + " :You cannot send messages to this channel whilst banned.");
				throw exception();
			}
			break;

		case ERR_TOOMANYCHANNELS:
			if (sender->getChannelCount() >= serv.getChanLimit()) {
				sender->stringAdd(":" + serv.getServName() + " 405 " + sender->getNickname()
					+ " " + param.channel_name + " :You are on too many channels");
				throw exception();
			}
			break;

		case ERR_ERRONEUSNICKNAME:
			if (param.indicator == 1) {
				sender->stringAdd(":" + serv.getServName() + " 432 * " + param.user_name + " :Erroneous Nickname");
				throw exception();
			}
			break;

		case ERR_NICKNAMEINUSE:
			if (param.indicator == 2) {
				sender->stringAdd(":" + serv.getServName() + " 433 * " + param.user_name + " :Nickname is already in use.");
				throw exception();
			}
			break;

		case ERR_USERNOTINCHANNEL:
			if (param.user && !param.user->isInChannel(param.channel)) {
				sender->stringAdd(":" + serv.getServName() + " 441 " + sender->getNickname()
					+ " " + param.user_name + " " + param.channel_name + " :They are not on that channel");
				throw exception();
			}
			break;

		case ERR_NOTONCHANNEL:
			if (!sender->isInChannel(param.channel)) {
				sender->stringAdd(":" + serv.getServName() + " 442 " + sender->getNickname()
					+ " " + param.channel_name + " :You're not on that channel!");
				throw exception();
			}
			break;

		case ERR_NOTREGISTERED:
			if (param.flag && !param.user->isConnected()) {
				sender->stringAdd(":" + serv.getServName() + " 451 " + sender->getNickname()
					+ " " + param.syntax + " :You have not registered.");
				throw exception();
			}
			break;

		case ERR_NEEDMOREPARAMS:
			if (count_param(param.comment) < param.match_idx) {
				sender->stringAdd(":" + serv.getServName() + " 461 " + sender->getNickname()
					+ " " + param.syntax + " :Not enough parameters.");
				throw exception();
			}
			break;

		case ERR_NOPERMFORHOST:
			if (!sender->isAuthorized()) {
				sender->stringAdd(":" + serv.getServName() + " 463 " + sender->getNickname()
					+ " :Your host isn't among the privileged");
				throw exception();
			}
			break;

		case ERR_PASSWDMISMATCH:
			if (param.comment != param.syntax) {
				sender->stringAdd(":" + serv.getServName() + " 463 " + sender->getNickname()
					+ " :Password incorrect");
				throw exception();
			}
			break;

		case ERR_CHANNELISFULL:
			if (param.channel->isFull()) {
				sender->stringAdd(":" + serv.getServName() + " 471 " + sender->getNickname()
					+ " " + param.channel_name + " :Cannot join channel (channel is full)");
				throw exception();
			}
			break;

		case ERR_UNKNOWNMODE:
			if (string("ovbilmnpstk").find(param.mode) == string::npos) {
				sender->stringAdd(":" + serv.getServName() + " 472 " + sender->getNickname()
					+ " " + param.mode + " :is not a recognised channel mode.");
				throw exception();
			}
			break;

		case ERR_INVITEONLYCHAN:
			if (!param.channel->isJoinableUser(param.user)) {
				sender->stringAdd(":" + serv.getServName() + " 473 " + sender->getNickname()
					+ " " + param.channel_name + " :Cannot join channel (invite only)");
				throw exception();
			}
			break;

		case ERR_BANNEDFROMCHAN:
			if (param.channel->isBanned(sender)) {
				sender->stringAdd(":" + serv.getServName() + " 474 " + sender->getNickname()
					+ " " + param.channel_name + " :Cannot join channel (you're banned)");
				throw exception();
			}
			break;

		case ERR_BADCHANNELKEY:
			if (!param.channel->checkPassword(param.comment)) {
				sender->stringAdd(":" + serv.getServName() + " 475 " + sender->getNickname()
					+ " " + param.channel_name + " :Cannot join channel (incorrect channel key)");
				throw exception();
			}
			break;

		case ERR_BADCHANMASK:
			if (param.channel_name.length() == 0 || param.channel_name[0] != '#' || param.channel_name.length() > 255) {
				sender->stringAdd(":" + serv.getServName() + " 476 " + sender->getNickname()
					+ " " + param.channel_name + " :Invalid channel name");
				throw exception();
			}
			break;

		case ERR_CHANOPRIVSNEEDED:
			if (!param.channel->isOperUser(sender)) {
				sender->stringAdd(":" + serv.getServName() + " 482 " + sender->getNickname()
					+ " " + param.channel_name + " :You must be a channel operator");
				throw exception();
			}
			break;

		case ERR_USERSDONTMATCH:
			if (sender != param.user) {
				sender->stringAdd(":" + serv.getServName() + " 502 " + param.user->getNickname()
					+ " :Can't view modes for other users");
				throw exception();
			}
			break;

		case ERR_INVALIDPARAM:
			if (param.mode == 'l' && stringToll(param.comment) < 0) {
				sender->stringAdd(":" + serv.getServName() + " 696 " + sender->getNickname()
					+ " " + param.channel_name + " " + param.mode + " " + param.comment + " :"
					+ "Invalid limit mode parameter. Syntax: <limit>.");
				throw exception();
			}
			break;

		case ERR_SPECIFYPARAM:
			if (param.indicator <= param.match_idx) {
				sender->stringAdd(":" + serv.getServName() + " 696 " + sender->getNickname()
					+ " " + param.channel_name + " " + param.mode + " * :You must specify a parameter for the "
					+ param.syntax + " mode. Syntax: <" + param.syntax + ">.");
				throw exception();
			}
			break;

		case ERR_ALREADYBANNED:
			if (param.channel->isBanned(param.comment)) {
				sender->stringAdd(":" + serv.getServName() + " 697 " + sender->getNickname()
					+ " " + param.channel_name + " " + param.comment + " " + param.mode
					+ " :Channel ban list already contains " + param.comment);
				throw exception();
			}
			break;

		case ERR_ISNOTBANNED:
		//  :irc.local 698 root #a root b :Channel ban list does not contain root
			if (!param.channel->isBanned(param.comment)) {
				sender->stringAdd(":" + serv.getServName() + " 698 " + sender->getNickname()
					+ " " + param.channel_name + " " + param.comment + " " + param.mode
					+ " :Channel ban list does not contain " + param.comment);
				throw exception();
			}
			break;
	}
}

void sendResponse(Server &serv, User *sender, t_rpl rpl_no, param_t param) {
	vector<User *> users;
	vector<User *>::iterator user_it;
	string temp;

	switch (rpl_no) {
		case RPL_UMODEIS:
			sender->stringAdd(":" + serv.getServName() + " 221 " + sender->getNickname()
				+ " " + param.user_name + " :" + param.comment);
			break;

		case RPL_WHOISUSER:
			sender->stringAdd(":" + serv.getServName() + " 311 " + sender->getNickname()
				+ " " + param.user_name + " " + param.user->getName() + " " + param.user->getIpAddr()
				+ " * :" + param.user->getName());
			break;

		case RPL_WHOISSERVER:
			sender->stringAdd(":" + serv.getServName() + " 312 " + sender->getNickname()
				+ " " + param.user_name + " " + serv.getServName() + " :Local IRC Server");
			break;

		case RPL_ENDOFWHO:
			sender->stringAdd(":" + serv.getServName() + " 315 " + sender->getNickname()
				+ " " + param.comment + " :End of /WHO list.");
			break;

		case RPL_WHOISIDLE:
			sender->stringAdd(":" + serv.getServName() + " 317 " + sender->getNickname()
				+ " " + param.user_name + " " + param.comment + param.user->getCreateTime()
				+ " :seconds idle, singon time");
			break;

		case RPL_ENDOFWHOIS:
			sender->stringAdd(":" + serv.getServName() + " 318 " + sender->getNickname()
				+ " " + param.user_name + " :End of /WHOIS list.");
			break;

		case RPL_LISTSTART:
			sender->stringAdd(":" + serv.getServName() + " 321 " + sender->getNickname()
				+ " Channel :User Name");
			break;

		case RPL_LIST:
			sender->stringAdd(":" + serv.getServName() + " 322 " + sender->getNickname()
				+ " " + param.channel_name + " " + param.comment);
			break;

		case RPL_LISTEND:
			sender->stringAdd(":" + serv.getServName() + " 323 " + sender->getNickname()
				+ " :End of channel list.");
			break;

		case RPL_CHANNELMODEIS:
			sender->stringAdd(":" + serv.getServName() + " 324 " + sender->getNickname()
				+ " " + param.channel_name + " :" + param.comment);
			break;

		case RPL_TIMESTAMP:
			sender->stringAdd(":" + serv.getServName() + " 329 " + sender->getNickname()
				+ " " + param.channel_name + " :" + param.channel->getCreateTime());
			break;

		case RPL_TOPIC:
			if (param.log != NULL) {
				sender->stringAdd(":" + serv.getServName() + " 332 " + sender->getName()
					+ " " + param.channel_name + " :" + param.log->getData());
			}
			break;

		case RPL_TOPICTIME:
			if (param.log != NULL) {
				sender->stringAdd(":" + serv.getServName() + " 333 " + sender->getName()
					+ " " + param.channel_name + " " + sender->getFormattedInfo() + " :" + param.log->getLogtime());
			}
			break;

		case RPL_INVITING:
			sender->stringAdd(":" + serv.getServName() + " 341 " + param.user_name
				+ " " + sender->getNickname() + " :" + param.channel_name);
			break;

		case RPL_WHOREPLY:
			if (param.channel && sender->getJoinChannel() == param.channel) {
				users = param.channel->getJoinUsers();
				for (user_it = users.begin(); user_it != users.end(); user_it++) {
					sender->stringAdd(":" + serv.getServName() + " 352 " + (*user_it)->getNickname() + " " + param.channel->getChannelName()
						+ " " + (*user_it)->getName() + " " + (*user_it)->getIpAddr() + " " + serv.getServName() + " " + (*user_it)->getNickname()
						+ (param.channel->isOperUser(*user_it) ? " H@ :0 " : " H :0 ") + (*user_it)->getName());
				}
			}
			else if (param.user) {
				sender->stringAdd(":" + serv.getServName() + " 352 " + param.user_name + " " + param.channel_name
					+ " " + param.user->getName() + " " + param.user->getIpAddr() + " " + serv.getServName() + " " + param.user_name
					+ (param.user->isChannelOper() ? " H@ :0 " : " H :0 ") + param.user->getName());
			}
			break;

		case RPL_NAMREPLY:
			users = param.channel->getJoinUsers();
			for (user_it = users.begin(); user_it != users.end(); user_it++) {
				temp += (param.channel->isOperUser(*user_it) ? "@" : "") + (*user_it)->getNickname();
				if (user_it + 1 != users.end())
					temp += " ";
			}
			sender->stringAdd(":" + serv.getServName() + " 353 " + sender->getNickname()
				+ " = " + param.channel_name + " :" + temp);
			break;

		case RPL_ENDOFNAMES:
			sender->stringAdd(":" + serv.getServName() + " 366 " + sender->getNickname()
				+ " " + param.channel_name + " :End of /NAMES list.");
			break;

		case RPL_BANLIST:
			sender->stringAdd(":" + serv.getServName() + " 367 " + sender->getNickname()
				+ " " + param.channel_name + " " + param.log->getData() + " " + param.log->getUserName()
				+ " :" + param.log->getLogtime());
			break;

		case RPL_ENDOFBANLIST:
			sender->stringAdd(":" + serv.getServName() + " 368 " + sender->getNickname()
				+ " " + param.channel_name + " :End of channel ban list");
			break;

		case RPL_HOSTNAME:
			sender->stringAdd(":" + serv.getServName() + " 378 " + sender->getNickname()
				+ " " + param.user_name + " :is connecting from " + param.user->getName() + "@"
				+ param.user->getIpAddr() + " " + param.user->getIpAddr());
			break;

		case RPL_USERMODES:
			sender->stringAdd(":" + serv.getServName() + " 379 " + sender->getNickname()
				+ " " + param.user_name + " :is using modes " + param.user->getModeString());
			break;
	}
}
