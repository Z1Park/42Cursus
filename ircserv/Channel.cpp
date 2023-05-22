#include "Channel.hpp"

Channel::Channel(string ch_name) : ch_name(ch_name), create_time(ulToString(time(NULL))),
		limit_count(20), topic(IrcLog()) {
	mode = CH_MODE_N | CH_MODE_T;
}

Channel::~Channel() {
}

Channel& Channel::operator=(const Channel& ref) {
	if (this != &ref) {
		ch_name = ref.ch_name;
		join_users = ref.join_users;
	}
	return *this;
}

bool Channel::operator==(const Channel& ref) {
	return (ch_name == ref.ch_name && opers == ref.opers
		&& limit_count == ref.limit_count && mode == ref.mode && join_users == ref.join_users);
}

void Channel::setChannelName(string name) {
	ch_name = name;
}

string Channel::getChannelName() const {
	return ch_name;
}

string Channel::getCreateTime() const {
	return create_time;
}


bool Channel::isOperUser(const User *user) const {
	return find(opers.begin(), opers.end(), user) != opers.end();
}

void Channel::setOperUser(User *user) {
	opers.push_back(user);
}

void Channel::unsetOperUser(User *user) {
	vector<User *const>::iterator it = find(opers.begin(), opers.end(), user);

	if (it != opers.end())
		opers.erase(it);
}


bool Channel::isEmpty() const {
	return join_users.empty();
}

bool Channel::isFull() const {
	return mode & CH_MODE_L && join_users.size() >= limit_count;
}

bool Channel::setChannelLimit(unsigned long long limit) {
	if (limit > 9223372036854775807)
		return false;
	limit_count = limit;
	return true;
}

bool Channel::setChannelLimit(string limit) {
	long long num = stringToll(limit);

	if (num == -1)
		return false;
	limit_count = num;
	return true;
}


void Channel::setPassword(string password) {
	if (password.length() >= 32)
		this->password = password.substr(0, 32);
	else
		this->password = password;
}

bool Channel::checkPassword(string password) const {
	return this->password == password;
}


void Channel::setTopic(string topic, string user) {
	this->topic = IrcLog(user, topic);
}

void Channel::unsetTopic() {
}

IrcLog& Channel::getTopic() {
	return topic;
}


void Channel::setModeFlag(int mode) {
	this->mode |= mode & 0xFF;
}

void Channel::unsetModeFlag(int mode) {
	this->mode &= ((mode & 0xFF) ^ 0xFF);
}

int Channel::getMode() const {
	return mode;
}

string Channel::getModeString() const {
	const string mode_flag[] =
		{"i", "k", "l", "m", "n", "p", "s", "t"};
	string mode_str = "+";

	for (int i = 0; i < 8; i++) {
		if (mode & (1 << i))
			mode_str += mode_flag[i];
	}
	if (mode & CH_MODE_K)
		mode_str += " " + password;
	if (mode & CH_MODE_L)
		mode_str += " :" + ulToString(limit_count);
	return mode_str;
}


void Channel::userJoin(User *user) {
	vector<User *>::iterator it;

	if (mode & CH_MODE_I) {
		it = find(invite_list.begin(), invite_list.end(), user);
		if (it != invite_list.end()) {
			invite_list.erase(it);
			join_users.push_back(user);
			if (opers.size() == 0)
				opers.push_back(user);
			return;
		}
	}
	if (join_users.size() == 0)
		opers.push_back(user);
	join_users.push_back(user);
}

void Channel::userLeave(User *user) {
	vector<User *>::iterator it = find(join_users.begin(), join_users.end(), user);

	if (it != join_users.end()) {
		unsetVoice(user);
		unsetOperUser(user);
		join_users.erase(it);
	}
}

vector<User *> Channel::getJoinUsers() const {
	return join_users;
}


vector<IrcLog> Channel::getBanList() const {
	return ban_list;
}

bool Channel::isBanned(User *user) {
	vector<IrcLog>::iterator it;
	for (it = ban_list.begin(); it != ban_list.end(); it++) {
		if (check_wildcard_match(it->getData(), user->getFormattedInfo()))
			return true;
	}
	return false;
}

bool Channel::isBanned(string banmask) {
	vector<IrcLog>::iterator it;
	for (it = ban_list.begin(); it != ban_list.end(); it++) {
		if (it->getData() == banmask)
			return true;
	}
	return false;
}

void Channel::ban(string user_name, string banmask) {
	ban_list.push_back(IrcLog(user_name, banmask));
}

void Channel::unban(string banmask) {
	vector<IrcLog>::iterator it;
	for (it = ban_list.begin(); it != ban_list.end(); it++) {
		if (it->getData() == banmask) {
			ban_list.erase(it);
			return;
		}
	}
}


bool Channel::hasVoice(User *user) {
	return find(voice_list.begin(), voice_list.end(), user) != voice_list.end();
}

void Channel::setVoice(User *user) {
	voice_list.push_back(user);
}

void Channel::unsetVoice(User *user) {
	vector<User *>::iterator it = find(voice_list.begin(), voice_list.end(), user);

	if (it != voice_list.end())
		voice_list.erase(it);
}


size_t Channel::getUserCount() const {
	return join_users.size();
}

bool Channel::isJoinableUser(User *user) const {
	if ((mode & CH_MODE_I) == 0)
		return true;
	return find(invite_list.begin(), invite_list.end(), user) != invite_list.end();
}

bool Channel::isJoinedUser(User *user) const {
	return find(join_users.begin(), join_users.end(), user) != join_users.end();
}

void Channel::addInviteUser(User *user) {
	if (find(invite_list.begin(), invite_list.end(), user) == invite_list.end())
		invite_list.push_back(user);
}

void Channel::broadcast(string msg) {
	vector<User *>::iterator it;
	for (it = join_users.begin(); it != join_users.end(); it++)
		(*it)->stringAdd(msg);
}
