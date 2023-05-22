#pragma once
#include "ircserv.hpp"

class Server {
	private:
		vector<User *> users;
		vector<Channel *> channels;
		string serv_name;
		string serv_id;
		string serv_ip_addr;
		int serv_port;
		size_t chan_limit;
		tm *create_time;
		string password;

	public:
		Server(string id, string ip_addr, int port);
		~Server();
		Server& operator=(const Server& ref);

		size_t getUserCount() const;
		size_t getInvisibleUserCount() const;
		size_t getChannelCount() const;
		size_t getChanLimit() const;

		User* getUser(string ip_addr, int port);
		User* getUser(string nickname);
		Channel* getChannel(string channel);
		string getServName() const;
		string getServId() const;
		string getServIpAddr() const;
		int getServPort() const;
		tm getCreateTime() const;
		string getPassword() const;
		void setPassword(string password);
		string getFormattedInfo() const;

		void setNickname(string ip_addr, int port, string nickname) const;
		int findMatchNickname(string nickname) const;
		User* createUser(string& buf, struct pollfd& poll_fd, string ip_addr, int port);
		Channel* userCreateChannel(User *user, string channel_name);
		void userJoinChannel(User *user, Channel *channel);
		void userLeaveChannel(User *user, Channel *channel);
		void userQuit(User *user);
		vector<Channel *> getAllChannels() const;
};
