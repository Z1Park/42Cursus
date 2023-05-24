#include "Server.hpp"

Server::Server(string id, string ip_addr, int port)
	: serv_name("irc.local"), serv_id(id), serv_ip_addr(ip_addr), serv_port(port),
	chan_limit(20) {
	time_t timestamp = time(NULL);

	create_time = localtime(&timestamp);
}

Server::~Server() {
	for (vector<User *>::iterator it = users.begin(); it != users.end(); it++)
		delete *it;
	users.clear();
	for (vector<Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
		delete *it;
	channels.clear();
}

Server& Server::operator=(const Server& ref) {
	if (this != &ref) {
		users = ref.users;
		channels = ref.channels;
		serv_name = ref.serv_name;
		serv_id = ref.serv_id;
		serv_ip_addr = ref.serv_ip_addr;
		memcpy(create_time, ref.create_time, sizeof(*create_time));
	}
	return *this;
}

size_t Server::getUserCount() const {
	return users.size();
}

size_t Server::getInvisibleUserCount() const {
	size_t count = 0;
	vector<User *const>::iterator it;

	for (it = users.begin(); it != users.end(); it++) {
		if ((*it)->getMode() & US_MODE_I)
			count++;
	}
	return count;
}

size_t Server::getChannelCount() const {
	return channels.size();
}

size_t Server::getChanLimit() const {
	return chan_limit;
}

User* Server::getUser(string ip_addr, int port) {
	for (vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
		if ((*it)->getIpAddr() == ip_addr && (*it)->getPort() == port)
			return *it;
	}
	return NULL;
}

User* Server::getUser(string nickname) {
	for (vector<User *const>::iterator it = users.begin(); it != users.end(); it++) {
		if ((*it)->getNickname() == nickname)
			return *it;
	}
	return NULL;
}

Channel* Server::getChannel(string channel) {
	for (vector<Channel *>::iterator it = channels.begin(); it != channels.end(); it++) {
		if ((*it)->getChannelName() == channel) {
			return *it;
		}
	}
	return NULL;
}

string Server::getServName() const {
	return serv_name;
}

string Server::getServId() const {
	return serv_id;
}

string Server::getServIpAddr() const {
	return serv_ip_addr;
}

int Server::getServPort() const {
	return serv_port;
}


tm Server::getCreateTime() const {
	return *create_time;
}

string Server::getPassword() const {
	return password;
}

void Server::setPassword(string password) {
	this->password = password;
}

string Server::getFormattedInfo() const {
	return serv_id + "!" + serv_name + "@" + serv_ip_addr;
}

void Server::setNickname(string ip_addr, int port, string nickname) const {
	for (vector<User *const>::iterator it = users.begin(); it != users.end(); it++) {
		if ((*it)->getIpAddr() == ip_addr && (*it)->getPort() == port)
			(*it)->setNickname(nickname);
	}
}

int Server::findMatchNickname(string nickname) const {
	if (isdigit(nickname[0]) != 0 || nickname.length() > 30)
		return 1;
	for (vector<User *const>::iterator it = users.begin(); it != users.end(); it++) {
		if ((*it)->getNickname() == nickname)
			return 2;
	}
	return 0;
}

User* Server::createUser(string& buf, struct pollfd& poll_fd, string ip_addr, int port) {
	for (vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
		if ((*it)->getIpAddr() == ip_addr && (*it)->getPort() == port)
			return *it;
	}
	User *new_user = new User(buf, poll_fd, ip_addr, port);
	users.push_back(new_user);
	return new_user;
}

Channel* Server::userCreateChannel(User *user, string channel_name) {
	if (channels.size() < 100) {
		Channel *channel = new Channel(channel_name);
		channel->setModeFlag(CH_MODE_T | CH_MODE_N);
		userJoinChannel(user, channel);
		channels.push_back(channel);
		return channel;
	}
	return NULL;
}

void Server::userJoinChannel(User *user, Channel *channel) {
	channel->userJoin(user);
	user->addJoinChannel(channel);
}

void Server::userLeaveChannel(User *user, Channel *channel) {
	user->removeJoinChannel(channel);
	channel->userLeave(user);
	vector<Channel *>::iterator it;
	if (channel->isEmpty())
	{
		for (it = channels.begin(); it != channels.end(); it++) {
			if ((*it) == channel) {
				channels.erase(it);
				delete channel;
				break;
			}
		}
	}
}

void Server::userQuit(User *user) {
	vector<Channel *> join_channels = user->getAllChannels();
	for (vector<Channel *>::iterator it = join_channels.begin(); it != join_channels.end(); it++) {
		userLeaveChannel(user, *it);
	}
	for (vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
		if (*it == user) {
			delete *it;
			users.erase(it);
			return;
		}
	}
}

vector<Channel *> Server::getAllChannels() const {
	return channels;
}
