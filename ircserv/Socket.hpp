#pragma once
#include "ircserv.hpp"

#define MAX_CONN 100

class Socket {
	private:
		int 				serv_fd;
		struct sockaddr_in	serv_addr;
		struct pollfd		poll_fd[MAX_CONN];
		string				ip_addr[MAX_CONN];
		int					port[MAX_CONN];
		string				rd_buf[MAX_CONN];
		string				wr_buf[MAX_CONN];

	public:
		Socket();
		~Socket();

		int getServFd() const;
		void setServFd(int fd);
		struct sockaddr_in getServAddr() const;
		void setServAddr(int sin_family, int sin_port, int s_addr);
		bool servBindAndListen();
		bool servPoll();
		void setNewPoll(Server &serv);
		void socketPolling(Server &serv, Command &command);

		void removePoll(int idx);
		void receivePoll(int idx, Server &serv, Command &command);
		void sendPoll(int idx);
};
