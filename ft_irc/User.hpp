#pragma once
#include "ircserv.hpp"


class User {
	private:
		const string create_time;
		string& buf;
		struct pollfd& poll_fd;
		string ip_addr;
		int port;
		int mode;
		bool registered;
		bool connected;
		bool authorized;
		string nickname;
		string name;
		vector<Channel *> join_channel;

	public:
		User(string& buf, struct pollfd& poll_fd);
		User(string& buf, struct pollfd& poll_fd, const string& ip_addr, const int port);
		User(const User& ref);
		~User();
		User& operator=(const User& ref);
		bool operator==(const User& ref);

		void stringAdd(string str);

		void setNickname(string new_nickname);
		string getNickname() const;

		string getCreateTime() const;

		void setName(string new_name);
		string getName() const;

		void setIpAddr(string new_ip_addr);
		string getIpAddr() const;

		void setPort(int new_port);
		int getPort() const;

		void setMode(string mode);
		void setModeFlag(int mode);
		void unsetModeFlag(int mode);
		int getMode() const;
		string getModeString() const;

		Channel* getJoinChannel() const;
		bool isChannelOper() const;
		vector<Channel *> getAllChannels() const;
		size_t getChannelCount() const;
		void addJoinChannel(Channel *channel);
		void removeJoinChannel(Channel *channel);

		bool isAuthorized() const;
		void authorize();

		bool isRegistered() const;
		void regist();

		bool isConnected() const;
		void connect();
		void disconnect();

		bool checkUserInfoFilled() const;
		string getFormattedInfo() const;
		bool isInChannel(Channel *channel);
};
