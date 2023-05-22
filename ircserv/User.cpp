#include "User.hpp"

User::User(string& buf, struct pollfd& poll_fd) : create_time(ulToString(time(NULL))), buf(buf), poll_fd(poll_fd), ip_addr(), port(0),
	mode(0), registered(false), connected(false), authorized(false), nickname("*"), name("*"), join_channel() {
}

User::User(string& buf,struct pollfd& poll_fd, const string& ip_addr, const int port)
	: create_time(ulToString(time(NULL))), buf(buf), poll_fd(poll_fd), ip_addr(ip_addr), port(port),
	mode(0), registered(false), connected(false), authorized(false), nickname("*"), name("*"), join_channel() {
}

User::User(const User& ref) : buf(ref.buf), poll_fd(ref.poll_fd), ip_addr(ref.ip_addr),
	port(ref.port), nickname(ref.nickname), name(ref.name), join_channel(ref.join_channel) {
}

User::~User() {
}

User& User::operator=(const User& ref) {
	nickname = ref.nickname;
	name = ref.name;
	ip_addr = ref.ip_addr;
	return *this;
}

bool User::operator==(const User& ref) {
	return (buf == ref.buf && nickname == ref.nickname && name == ref.name
		&& ip_addr == ref.ip_addr && port == ref.port && join_channel == ref.join_channel);
}


void User::setNickname(string new_nickname) {
	nickname = new_nickname;
}

string User::getNickname() const {
	return nickname;
}


void User::setName(string new_name) {
	name = new_name;
}

string User::getName() const {
	return name;
}


string User::getCreateTime() const {
	return create_time;
}


void User::setIpAddr(string new_ip_addr) {
	ip_addr = new_ip_addr;
}

string User::getIpAddr() const {
	return ip_addr;
}


void User::setPort(int new_port) {
	port = new_port;
}

int User::getPort() const {
	return port;
}


void User::stringAdd(string str) {
	buf += str + "\r\n";
	poll_fd.revents |= POLLOUT;
}


void User::setMode(string mode_str) {
	const string mode_flag[] = {"i", "s", "w", "o"};
	for (int i = 0; i < 4; i++) {
		if (mode_str.find(mode_flag[i]) != mode_str.npos)
			mode |= (1 << i);
	}
}

void User::setModeFlag(int mode) {
	this->mode |= mode & 0xFF;
}

void User::unsetModeFlag(int mode) {
	this->mode &= ((mode & 0xFF) ^ 0xFF);
}

int User::getMode() const {
	return mode;
}

string User::getModeString() const {
	const string mode_flag[] = {"i", "s", "w", "o"};
	string mode_str = "+";

	for (int i = 0; i < 4; i++) {
		if (mode & (1 << i))
			mode_str += mode_flag[i];
	}
	return mode_str;
}


Channel* User::getJoinChannel() const {
	return (join_channel.empty()) ? NULL : join_channel.back();
}

bool User::isChannelOper() const {
	Channel *channel = getJoinChannel();

	if (channel == NULL)
		return false;
	return channel->isOperUser(this);
}

vector<Channel *> User::getAllChannels() const {
	return join_channel;
}

size_t User::getChannelCount() const {
	return join_channel.size();
}

void User::addJoinChannel(Channel *channel) {
	vector<Channel *>::iterator it;

	it = find(join_channel.begin(), join_channel.end(), channel);
	if (it != join_channel.end())
		join_channel.erase(it);
	join_channel.push_back(channel);
}

void User::removeJoinChannel(Channel *channel) {
	vector<Channel *>::iterator it;

	it = find(join_channel.begin(), join_channel.end(), channel);
	if (it != join_channel.end())
		join_channel.erase(it);
}


bool User::isAuthorized() const {
	return authorized;
}

void User::authorize() {
	authorized = true;
}


bool User::isRegistered() const {
	return registered;
}

void User::regist() {
	registered = true;
}


bool User::isConnected() const {
	return connected;
}

void User::connect() {
	connected = true;
}

void User::disconnect() {
	connected = false;
}


bool User::checkUserInfoFilled() const {
	return name != "*" && nickname != "*";
}

string User::getFormattedInfo() const {
	return nickname + "!" + name + "@" + ip_addr;
}

bool User::isInChannel(Channel *channel) {
	return find(join_channel.begin(), join_channel.end(), channel) != join_channel.end();
}
