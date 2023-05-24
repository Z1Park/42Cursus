#pragma once
#include "types.hpp"

class IrcLog {
	private:
		string data;
		string logtime;
		string user_name;

	public:
		IrcLog();
		IrcLog(string user_name, string data);
		~IrcLog();

		string getData() const;
		string getLogtime() const;
		string getUserName() const;
};
