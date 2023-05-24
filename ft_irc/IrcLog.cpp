#include "IrcLog.hpp"

IrcLog::IrcLog() : data(), logtime(ulToString(time(NULL))), user_name() {}

IrcLog::IrcLog(string user_name, string data) : data(data), logtime(ulToString(time(NULL))), user_name(user_name) {};

IrcLog::~IrcLog() {}

string IrcLog::getData() const {
	return data;
}

string IrcLog::getLogtime() const {
	return logtime;
}

string IrcLog::getUserName() const {
	return user_name;
}
