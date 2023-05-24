#include "Command.hpp"

Command::Command(Server& serv) : serv(serv) {
	cmd_map.insert(make_pair("CAP", cmd_info(0, false, static_cast<void (Command::*)(User*, string)>(NULL))));
	cmd_map.insert(make_pair("NICK", cmd_info(1, false, &Command::set_nickname)));
	cmd_map.insert(make_pair("USER", cmd_info(4, false, &Command::set_user_info)));
	cmd_map.insert(make_pair("PING", cmd_info(1, false, &Command::ping_pong)));
	cmd_map.insert(make_pair("JOIN", cmd_info(1, true, &Command::join_channel)));
	cmd_map.insert(make_pair("MODE", cmd_info(1, true, &Command::check_and_set_mode)));
	cmd_map.insert(make_pair("WHO", cmd_info(0, true, &Command::send_who_info)));
	cmd_map.insert(make_pair("WHOIS", cmd_info(1, true, &Command::send_whois_info)));
	cmd_map.insert(make_pair("PRIVMSG", cmd_info(2, true, &Command::receive_message)));
	cmd_map.insert(make_pair("INVITE", cmd_info(2, true, &Command::invite_user)));
	cmd_map.insert(make_pair("TOPIC", cmd_info(1, true, &Command::set_topic)));
	cmd_map.insert(make_pair("KICK", cmd_info(2, true, &Command::kick_user)));
	cmd_map.insert(make_pair("LIST", cmd_info(0, true, &Command::user_list)));
	cmd_map.insert(make_pair("PART", cmd_info(1, true, &Command::leave_channel)));
	cmd_map.insert(make_pair("QUIT", cmd_info(0, false, &Command::quit_client)));
}

void Command::start_connect(User &user) {
	string ip_addr = user.getIpAddr();
	string name = user.getName();
	string nickname = user.getNickname();
	string serv_name = serv.getServName();
	string user_count = ulToString(serv.getUserCount());
	string vis_user_count = ulToString(serv.getUserCount() - serv.getInvisibleUserCount());
	string inv_user_count = ulToString(serv.getInvisibleUserCount());
	string channel_count = ulToString(serv.getChannelCount());

	user.connect();
	user.stringAdd(":" + serv_name + " NOTICE " + nickname + " :*** Could not resolve your hostname: "
					+ "Request timed out; using your IP address (" + ip_addr + ") instead.");
	user.stringAdd(":" + serv_name + " 001 " + nickname + " :Welcome to the Localnet IRC Network "
					+ nickname + "!" + name + "@" + ip_addr);
	user.stringAdd(":" + serv_name + " 002 " + nickname + " :Your host is " + serv_name + ", running version InspIRCd-3");
	tm serv_time = serv.getCreateTime();
	char time_buf[100];
	strftime(time_buf, 100, "%H:%M:%S %b %d %Y", &serv_time);
	user.stringAdd(":" + serv_name + " 003 " + nickname + " :This server was created " + time_buf);
	user.stringAdd(":" + serv_name + " 004 " + nickname + " " + serv_name + " InspIRCd-3 iosw biklmnopstv :bklov");
	user.stringAdd(":" + serv_name + " 005 " + nickname + " CASEMAPPING=rfc1459 CHANLIMIT=#:20 "
					+ "CHANMODES=b,k,l,imnpst CHANNELLEN=64 CHANTYPES=# ELIST=CMNTU HOSTLEN=64 "
					+ "KEYLEN=32 KICKLEN=255 LINELEN=512 MAXLIST=b:100 :are supported by this server");
	user.stringAdd(":" + serv_name + " 005 " + nickname + " NETWORK=Localnet NICKLEN=30 PREFIX=(ov)@+ SAFELIST "
					+ "STATUSMSG=@+ TOPICLEN=307 USERLEN=10 USERMODES=,,s,iow WHOX :are supported by this server");
	user.stringAdd(":" + serv_name + " 251 " + nickname + " :There are " + vis_user_count
					+ " users and " + inv_user_count + " invisible on 1 servers");
	user.stringAdd(":" + serv_name + " 253 " + nickname + " 1 :unknown connections");
	user.stringAdd(":" + serv_name + " 254 " + nickname + " " + channel_count + " :channels formed");
	user.stringAdd(":" + serv_name + " 255 " + nickname + " I have " + user_count + " clients and 0 servers");
	user.stringAdd(":" + serv_name + " 265 " + nickname + " Current local users: " + user_count + "  Max: " + user_count);
	user.stringAdd(":" + serv_name + " 266 " + nickname + " Current global users: " + user_count + "  Max: " + user_count);
	user.stringAdd(":" + serv_name + " 375 " + nickname + " :" + serv_name + " message of the day");
	user.stringAdd(":" + serv_name + " 372 " + nickname + " : **************************************************");
	user.stringAdd(":" + serv_name + " 372 " + nickname + " : *             H    E    L    L    O              *");
	user.stringAdd(":" + serv_name + " 372 " + nickname + " : **************************************************");
	user.stringAdd(":" + serv_name + " 376 " + nickname + " :End of message of the day.");
}

void Command::set_nickname(User* sender,  string data) {
	vector<Channel *> join_channels;
	map<string, User *> all_user;
	param_t param;

	param.user_name = data;
	param.indicator = serv.findMatchNickname(data);
	try {
		checkError(serv, sender, ERR_NOPERMFORHOST, param);
		checkError(serv, sender, ERR_ERRONEUSNICKNAME, param);
		checkError(serv, sender, ERR_NICKNAMEINUSE, param);
		if (!sender->isConnected()) {
			sender->setNickname(param.user_name);
			if (sender->isRegistered())
				start_connect(*sender);
		}
		else {
			sender->stringAdd(":" + sender->getFormattedInfo() + " NICK :" + param.user_name);
			join_channels = sender->getAllChannels();
			for (vector<Channel *>::iterator it = join_channels.begin(); it != join_channels.end(); it++) {
				vector<User *> temp = (*it)->getJoinUsers();
				for (vector<User *>::iterator t_it = temp.begin(); t_it != temp.end(); t_it++) {
					all_user.insert(make_pair((*t_it)->getNickname(), *t_it));
				}
			}
			all_user.erase(sender->getNickname());
			for (map<string, User *>::iterator it = all_user.begin(); it != all_user.end(); it++)
				it->second->stringAdd(":" + sender->getFormattedInfo() + " NICK :" + param.user_name);
			sender->setNickname(param.user_name);
		}
	} catch (exception&) {}
}

bool Command::check_password(User* sender, string data) {
	string serv_password = serv.getPassword();
	param_t param;

	param.syntax = serv_password;
	param.comment = data;
	try {
		checkError(serv, sender, ERR_PASSWDMISMATCH, param);
		sender->authorize();
		return true;
	} catch (exception&) {
		serv.userQuit(sender);
		return false;
	}
}

bool Command::set_channel_mode(Channel *channel, User *sender, channel_mode_t mode) {
	param_t param;
	param.channel = channel;
	param.channel_name = channel->getChannelName();
	param.mode = mode.mode;

	switch (mode.mode) {
		case 'o':
			param.user_name = mode.param;
			param.user = serv.getUser(param.user_name);
			checkError(serv, sender, ERR_NOSUCHNICK, param);
			if (channel->isJoinedUser(param.user) && !channel->isOperUser(param.user)) {
				param.channel->setOperUser(param.user);
				return true;
			}
			return false;

		case 'v':
			param.user_name = mode.param;
			param.user = serv.getUser(param.user_name);
			checkError(serv, sender, ERR_NOSUCHNICK, param);
			if (channel->isJoinedUser(param.user) && !channel->hasVoice(param.user)) {
				channel->setVoice(param.user);
				return true;
			}
			return false;

		case 'b':
			param.comment = create_banmask(mode.param);
			checkError(serv, sender, ERR_ALREADYBANNED, param);
			channel->ban(sender->getNickname(), param.comment);
			channel->broadcast(":" + sender->getFormattedInfo() + " MODE " + param.channel_name
				+ " +b :" + param.comment);
			return true;

		case 'i':
			if (!(channel->getMode() & CH_MODE_I)) {
				channel->setModeFlag(CH_MODE_I);
				return true;
			}
			return false;

		case 'l':
			if (!(channel->getMode() & CH_MODE_L)) {
				channel->setModeFlag(CH_MODE_L);
				channel->setChannelLimit(mode.param);
				return true;
			}
			return false;

		case 'm':
			if (!(channel->getMode() & CH_MODE_M)) {
				channel->setModeFlag(CH_MODE_M);
				return true;
			}
			return false;

		case 'p':
			if (!(channel->getMode() & CH_MODE_P)) {
				channel->setModeFlag(CH_MODE_P);
				return true;
			}
			return false;

		case 's':
			if (!(channel->getMode() & CH_MODE_S)) {
				channel->setModeFlag(CH_MODE_S);
				return true;
			}
			return false;

		case 't':
			if (!(channel->getMode() & CH_MODE_T)) {
				channel->setModeFlag(CH_MODE_T);
				return true;
			}
			return false;

		case 'k':
			if (!(channel->getMode() & CH_MODE_K)) {
				channel->setModeFlag(CH_MODE_K);
				channel->setPassword(mode.param);
				return true;
			}
			return false;
	}
	return false;
}

bool Command::unset_channel_mode(Channel *channel, User *sender, channel_mode_t mode) {
	param_t param;
	param.channel = channel;
	param.channel_name = channel->getChannelName();
	param.mode = mode.mode;

	switch (mode.mode) {
		case 'o':
			param.user_name = mode.param;
			param.user = serv.getUser(param.user_name);
			checkError(serv, sender, ERR_NOSUCHNICK, param);
			if (channel->isJoinedUser(param.user) && channel->isOperUser(param.user)) {
				param.channel->unsetOperUser(param.user);
				return true;
			}
			return false;

		case 'v':
			param.user_name = mode.param;
			param.user = serv.getUser(param.user_name);
			checkError(serv, sender, ERR_NOSUCHNICK, param);
			if (channel->isJoinedUser(param.user) && channel->hasVoice(param.user)) {
				channel->unsetVoice(param.user);
				return true;
			}
			return false;

		case 'b':
			param.comment = mode.param;
			checkError(serv, sender, ERR_ISNOTBANNED, param);
			channel->unban(param.comment);
			channel->broadcast(":" + sender->getFormattedInfo() + " MODE " + param.channel_name
				+ " -b :" + param.comment);
			return true;

		case 'i':
			if (channel->getMode() & CH_MODE_I) {
				channel->unsetModeFlag(CH_MODE_I);
				return true;
			}
			return false;

		case 'l':
			if (channel->getMode() & CH_MODE_L) {
				channel->unsetModeFlag(CH_MODE_L);
				return true;
			}
			return false;

		case 'm':
			if (channel->getMode() & CH_MODE_M) {
				channel->unsetModeFlag(CH_MODE_M);
				return true;
			}
			return false;

		case 'p':
			if (channel->getMode() & CH_MODE_P) {
				channel->unsetModeFlag(CH_MODE_P);
				return true;
			}
			return false;

		case 's':
			if (channel->getMode() & CH_MODE_S) {
				channel->unsetModeFlag(CH_MODE_S);
				return true;
			}
			return false;

		case 't':
			if (channel->getMode() & CH_MODE_T) {
				channel->unsetModeFlag(CH_MODE_T);
				return true;
			}
			return false;

		case 'k':
			if (channel->getMode() & CH_MODE_K) {
				channel->unsetModeFlag(CH_MODE_K);
				channel->setPassword("");
				return true;
			}
			return false;
	}
	return false;
}


void Command::set_user_info(User* sender, string data) {
	string name = string_split(data, " :").front();

	sender->setName(name);
	sender->regist();
	if (sender->checkUserInfoFilled() && !sender->isConnected())
		start_connect(*sender);
}

void Command::ping_pong(User* sender, string data) {
	(void)data;
	string serv_name = serv.getServName();

	sender->stringAdd(":" + serv_name + " PONG " + serv_name + " :" + serv_name);
}

void Command::join_channel(User* sender, string data) {
	vector<string> line_vec = string_split(data, " ");
	vector<string> channel_vec = string_split(line_vec[0], ",");
	map<string, string> join_map;

	if (line_vec.size() >= 2) {
		vector<string> key_vec = string_split(line_vec[1], ",");
		for (size_t i = 0; i < channel_vec.size(); i++)
			join_map.insert(make_pair(channel_vec[i], key_vec[i]));
	}
	else {
		for (size_t i = 0; i < channel_vec.size(); i++)
			join_map.insert(make_pair(channel_vec[i], ""));
	}

	map<string, string>::iterator it;
	for (it = join_map.begin(); it != join_map.end(); it++) {
		param_t param;
		param.channel_name = (*it).first;
		param.comment =(*it).second;
		param.channel = serv.getChannel(param.channel_name);
		try {
			checkError(serv, sender, ERR_TOOMANYCHANNELS, param);
			checkError(serv, sender, ERR_BADCHANMASK, param);
			if (param.channel) {
				param.user = sender;
				checkError(serv, sender, ERR_BADCHANNELKEY, param);
				checkError(serv, sender, ERR_INVITEONLYCHAN, param);
				checkError(serv, sender, ERR_BANNEDFROMCHAN, param);
				checkError(serv, sender, ERR_CHANNELISFULL, param);
				serv.userJoinChannel(sender, param.channel);
			}
			else {
				param.channel = serv.userCreateChannel(sender, param.channel_name);
				checkError(serv, sender, ERR_NOSUCHCHANNEL, param);
			}
			param.log = &param.channel->getTopic();
			if (param.log->getData() != "") {
				sendResponse(serv, sender, RPL_TOPIC, param);
				sendResponse(serv, sender, RPL_TOPICTIME, param);
			}
			param.channel->broadcast(":" + sender->getFormattedInfo() + " JOIN :" + param.channel_name);
			sendResponse(serv, sender, RPL_NAMREPLY, param);
			sendResponse(serv, sender, RPL_ENDOFNAMES, param);
		} catch (exception&) {}
	}
}

void Command::user_mode_check(User *user, vector<string> splited) {
	User *found_user = serv.getUser(splited.front());
	string serv_name = serv.getServName();
	param_t param;

	param.user = found_user;
	try {
		checkError(serv, user, ERR_NOSUCHNICK, param);
		checkError(serv, user, ERR_USERSDONTMATCH, param);
		if (splited.size() == 1) {
			param.user_name = splited[0];
			param.comment = param.user->getModeString();
			sendResponse(serv, user, RPL_UMODEIS, param);
		}
		else {
			user->setMode(splited.back());
			user->stringAdd(":" + user->getFormattedInfo() + " MODE " + user->getNickname() + " :" + user->getModeString());
		}
	} catch (exception&) {}
}

void Command::send_banlist(User *sender, param_t &param) {
	vector<IrcLog> bans = param.channel->getBanList();
	vector<IrcLog>::iterator ban_it;
	for (ban_it = bans.begin(); ban_it != bans.end(); ban_it++) {
		param.log = &*ban_it;
		sendResponse(serv, sender, RPL_BANLIST, param);
	}
	sendResponse(serv, sender, RPL_ENDOFBANLIST, param);
}

void Command::mode_channel(User *sender, vector<string> line_vec) {
	param_t param;
	param.channel_name = line_vec[0];
	param.channel = serv.getChannel(line_vec[0]);
	try {
		checkError(serv, sender, ERR_NOSUCHCHANNEL, param);
		if (line_vec.size() == 1) {
			param.comment = param.channel->getModeString();
			sendResponse(serv, sender, RPL_CHANNELMODEIS, param);
			sendResponse(serv, sender, RPL_TIMESTAMP, param);
		}
		else {
			char flag = '+';
			if (line_vec[1][0] == '-')
				flag = '-';
			if (line_vec[1].find('b') != string::npos) {
				if ((line_vec[1][0] != '+' && line_vec[1][0] != '-' && line_vec[1].size() > 1)
					|| ((line_vec[1][0] == '+' || line_vec[1][0] == '-') && line_vec[1].size() > 2)) return;
				if (line_vec.size() == 2) {
					send_banlist(sender, param);
					return;
				}
				channel_mode_t ch_mode = make_ch_mode('b', line_vec[2]);
				if (flag == '+')
					set_channel_mode(param.channel, sender, ch_mode);
				else
					unset_channel_mode(param.channel, sender, ch_mode);
				return;
			}
			vector<channel_mode_t> parsed_line = parse_mode(serv, sender, line_vec, flag);
			vector<channel_mode_t> success_list;
			vector<channel_mode_t>::iterator it;
			for (it = parsed_line.begin(); it != parsed_line.end(); it++) {
				try {
					checkError(serv, sender, ERR_CHANOPRIVSNEEDED, param);
					if (((flag == '+' && set_channel_mode(param.channel, sender, *it))
						|| (flag == '-' && unset_channel_mode(param.channel, sender, *it))))
						success_list.push_back(*it);
				} catch (exception &) {}
			}
			if (success_list.size() > 0)
				param.channel->broadcast(create_modestr(sender, param.channel, success_list, flag));
		}
	} catch (exception&) {}
}

void Command::check_and_set_mode(User* sender, string data) {
	vector<string> line_vec = string_split(data, " ");

	if (line_vec.front()[0] == '#')
		mode_channel(sender, line_vec);
	else
		user_mode_check(sender, line_vec);
}

void Command::send_who_info(User* sender, string data) {
	vector<string> line_vec = string_split(data, " ");
	param_t param;

	if (line_vec[0][0] == '#') {
		param.channel_name = line_vec[0];
		param.channel = serv.getChannel(line_vec[0]);
		param.user = NULL;
	}
	else {
		param.user_name = line_vec[0];
		param.user = serv.getUser(line_vec[0]);
		if (param.user) {
			param.channel = param.user->getJoinChannel();
			if (param.channel == NULL)
				param.channel_name = "*";
			else
				param.channel_name = param.channel->getChannelName();
		}
		param.channel = NULL;
	}
	param.comment = line_vec[0];
	sendResponse(serv, sender, RPL_WHOREPLY, param);
	sendResponse(serv, sender, RPL_ENDOFWHO, param);
}

void Command::send_whois_info(User* sender, string data) {
	vector<string> names = string_split(data, " ");
	vector<string> name_vec;
	vector<string>::iterator it;
	param_t param;

	if (names.size() > 1)
		name_vec = string_split(names[1], ",");
	else
		name_vec.push_back(names[0]);
	for (it = name_vec.begin(); it != name_vec.end(); it++) {
		try {
			param.user_name = *it;
			param.user = serv.getUser(*it);
			checkError(serv, sender, ERR_NOSUCHNICK, param);
			param.comment = time(NULL) - atoi(param.user->getCreateTime().c_str());
			sendResponse(serv, sender, RPL_WHOISUSER, param);
			if (sender == param.user)
				sendResponse(serv, sender, RPL_HOSTNAME, param);
			sendResponse(serv, sender, RPL_WHOISSERVER, param);
			if (sender == param.user)
				sendResponse(serv, sender, RPL_USERMODES, param);
			sendResponse(serv, sender, RPL_WHOISIDLE, param);
			sendResponse(serv, sender, RPL_ENDOFWHOIS, param);
		} catch (exception&) {}
	}
}

void Command::receive_message(User* sender, string data) {
	string name = string_split(data, " ")[0];
	string msg = data.substr(name.length() + 1);
	param_t param;

	if (name[0] == '#') {
		param.channel_name = name;
		param.channel = serv.getChannel(param.channel_name);
	} else {
		param.user_name = name;
		param.user = serv.getUser(name);
	}
	try {
		if (name[0] != '#') {
			checkError(serv, sender, ERR_NOSUCHNICK, param);
			param.user->stringAdd(":" + sender->getFormattedInfo() + " PRIVMSG " + data);
		}
		else {
			checkError(serv, sender, ERR_NOSUCHCHANNEL, param);
			if (param.channel->getMode() & CH_MODE_M) {
				param.mode = 'm';
				checkError(serv, sender, ERR_CANNOTSENDTOCHAN, param);
			}
			param.mode = 'b';
			checkError(serv, sender, ERR_CANNOTSENDTOCHAN, param);
			vector<User *>ch_users = param.channel->getJoinUsers();
			for (vector<User *>::iterator it = ch_users.begin(); it != ch_users.end(); it++) {
				if (*it != sender)
					(*it)->stringAdd(":" + sender->getFormattedInfo() + " PRIVMSG " + data);
			}
			if (msg == ":42seoul")
				param.channel->broadcast(":42seoul_bot!ircserv@127.0.0.1 PRIVMSG " + param.channel_name + " :" + BOT_MSG);
		}
	} catch (exception &) {}
}

void Command::invite_user(User* sender, string data) {
	param_t param;

	param.channel_name = data.substr(data.find_first_of(' ') + 1, data.length());
	param.channel = serv.getChannel(param.channel_name);
	param.user_name = data.substr(0, data.find_first_of(' '));
	param.user = serv.getUser(param.user_name);
	try {
		checkError(serv, sender, ERR_NOSUCHCHANNEL, param);
		checkError(serv, sender, ERR_NOSUCHNICK, param);
		checkError(serv, sender, ERR_CHANOPRIVSNEEDED, param);
		param.channel->addInviteUser(param.user);
		sendResponse(serv, sender, RPL_INVITING, param);
		param.user->stringAdd(":" + sender->getFormattedInfo() + " INVITE "
			+ sender->getNickname() + " :" + param.channel_name);
	} catch (exception&) {}
}

void Command::set_topic(User* sender, string data) {
	vector<string> line_vec = string_split(data, " ");
	vector<User *> ch_users;
	param_t param;

	param.channel_name = line_vec[0];
	param.channel = serv.getChannel(line_vec[0]);
	try {
		checkError(serv, sender, ERR_NOSUCHCHANNEL, param);
		ch_users = param.channel->getJoinUsers();
		param.channel->setTopic(data, sender->getNickname());
		for (vector<User *>::iterator it = ch_users.begin(); it != ch_users.end(); it++)
			(*it)->stringAdd(":" + sender->getFormattedInfo() + " TOPIC " + data);
	} catch (exception&) {}
}

void Command::kick_user(User* sender, string data) {
	vector<string> line_vec = string_split(data, " ");
	vector<string>::iterator it;
	param_t param;

	param.channel_name = line_vec[0];
	param.channel = serv.getChannel(line_vec[0]);
	param.user_name = line_vec[1];
	param.user = serv.getUser(line_vec[1]);
	for (it = line_vec.begin() + 2; it != line_vec.end(); it++)
		param.comment += *it;

	if (param.comment.length() > 255)
		param.comment = param.comment.substr(0, 255);
	try {
		checkError(serv, sender, ERR_NOSUCHCHANNEL, param);
		checkError(serv, sender, ERR_NOSUCHNICK, param);
		checkError(serv, sender, ERR_NOTONCHANNEL, param);
		checkError(serv, sender, ERR_USERNOTINCHANNEL, param);
		checkError(serv, sender, ERR_CHANOPRIVSNEEDED, param);
		param.channel->broadcast(":" + sender->getFormattedInfo() + " KICK " + line_vec[0]
			+ " " + line_vec[1] + " " + line_vec[2]);
		serv.userLeaveChannel(param.user, param.channel);
	} catch (exception &) {}
}

void Command::user_list(User* sender, string data) {
	Channel *channel = serv.getChannel(data);
	vector<Channel *> all_channels;
	vector<Channel *>::iterator it;
	param_t param;

	sendResponse(serv, sender, RPL_LISTSTART, param);
	if (channel != NULL)
		all_channels.push_back(channel);
	else
		all_channels = serv.getAllChannels();
	for (it = all_channels.begin(); it != all_channels.end(); it++) {
		if ((*it)->getMode() & CH_MODE_S)
			continue;
		if ((*it)->getMode() & CH_MODE_P) {
			param.channel_name = "*";
			param.comment = ulToString((*it)->getUserCount()) + " :";
		}
		else {
			param.channel_name = (*it)->getChannelName();
			param.comment = ulToString((*it)->getUserCount()) + " :[" + (*it)->getModeString() + "]";
		}
		sendResponse(serv, sender, RPL_LIST, param);
	}
	sendResponse(serv, sender, RPL_LISTEND, param);
}

void Command::leave_channel(User* sender, string data) {
	string ch_name = string_split(data, " ").front();
	param_t param;

	param.channel = serv.getChannel(ch_name);
	try {
		checkError(serv, sender, ERR_NOSUCHCHANNEL, param);
		vector<User *> ch_users = param.channel->getJoinUsers();
		for (vector<User *>::iterator it = ch_users.begin(); it != ch_users.end(); it++)
			(*it)->stringAdd(":" + sender->getFormattedInfo() + " PART :" + ch_name);
		param.channel->userLeave(sender);
		serv.userLeaveChannel(sender, param.channel);
	} catch (exception&) {}
}

void Command::quit_client(User* sender, string data) {
	Channel *channel;
	string quit_msg = data.substr(0, data.length());

	sender->stringAdd("ERROR :Closing link: (" + sender->getName() + "@" + sender->getIpAddr() + ") [Quit: " + data + "]");
	channel = sender->getJoinChannel();
	while (channel != NULL) {
		vector<User *> ch_users = channel->getJoinUsers();
		for (vector<User *>::iterator it = ch_users.begin(); it != ch_users.end(); it++)
			(*it)->stringAdd(":" + sender->getFormattedInfo() + " QUIT :Quit: " + channel->getChannelName());
		channel->userLeave(sender);
		serv.userLeaveChannel(sender, channel);
		channel = sender->getJoinChannel();
	}
	serv.userQuit(sender);
}

Command::~Command() {
	cmd_map.clear();
}

Command& Command::operator=(const Command& ref) {
	cmd_map = ref.cmd_map;
	return *this;
}


bool Command::find_command(User* sender, string buf) {
	vector<string> line_vec = string_split(buf, "\r\n");
	vector<string>::iterator vec_it;

	for (vec_it = line_vec.begin(); vec_it != line_vec.end(); vec_it++) {
		size_t idx = vec_it->find_first_of(' ', 0);
		string cmd = vec_it->substr(0, idx);
		string data = "";
		if (cmd.length() != vec_it->length())
			data = vec_it->substr(idx + 1, (*vec_it).length());
		param_t param;
		try {
			if (cmd == "PASS") {
				param.user = sender;
				param.syntax = cmd;
				param.comment = data;
				param.match_idx = 1;
				checkError(serv, sender, ERR_NEEDMOREPARAMS, param);
				if (!Command::check_password(sender, data))
					return false;
			}
			else {
				map<string, cmd_info>::iterator cmd_found = cmd_map.find(cmd);
				if (cmd_found != cmd_map.end() && cmd_found->second.func != NULL) {
					param.user = sender;
					param.syntax = cmd;
					param.flag = cmd_found->second.register_needed;
					param.comment = data;
					param.match_idx = cmd_found->second.min_param;
					checkError(serv, sender, ERR_NEEDMOREPARAMS, param);
					checkError(serv, sender, ERR_NOTREGISTERED, param);
					(this->*cmd_found->second.func)(sender, data);
				}
				if (cmd == "QUIT")
					return false;
			}
		} catch (exception&) {}
	}
	return true;
}
