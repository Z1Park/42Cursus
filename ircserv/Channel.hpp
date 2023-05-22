#pragma once
#include "ircserv.hpp"
#include "User.hpp"
#include "IrcLog.hpp"

class Channel {
	private:
		string ch_name;
		vector<User *> opers;
		const string create_time;
		unsigned long long limit_count;
		string password;
		IrcLog topic;
		int mode;
		vector<User *> join_users;
		vector<User *> invite_list;
		vector<User *> voice_list;
		vector<IrcLog> ban_list;

	public:
		Channel(string ch_name);
		~Channel();
		Channel& operator=(const Channel& ref);
		bool operator==(const Channel& ref);

		void setChannelName(string name);
		string getChannelName() const;
		string getCreateTime() const;

		bool isOperUser(const User *user) const;
		void setOperUser(User *user);
		void unsetOperUser(User *user);

		bool isEmpty() const;
		bool isFull() const;
		bool setChannelLimit(unsigned long long limit);
		bool setChannelLimit(string limit);

		void setPassword(string password);
		bool checkPassword(string password) const;

		void setTopic(string topic, string user);
		void unsetTopic();
		IrcLog& getTopic();

		void setModeFlag(int mode);
		void unsetModeFlag(int mode);
		int getMode() const;
		string getModeString() const;

		void userJoin(User *user);
		void userLeave(User *user);
		vector<User *> getJoinUsers() const;

		vector<IrcLog> getBanList() const;
		bool isBanned(User *user);
		bool isBanned(string str);
		void ban(string user_name, string banmask);
		void unban(string banmask);

		bool hasVoice(User *user);
		void setVoice(User *user);
		void unsetVoice(User *user);

		size_t getUserCount() const;
		bool isJoinableUser(User *user) const;
		bool isJoinedUser(User *user) const;
		void addInviteUser(User *user);
		void broadcast(string msg);
};
