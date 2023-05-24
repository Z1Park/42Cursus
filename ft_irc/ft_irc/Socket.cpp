#include "Socket.hpp"

Socket::Socket() {
}

Socket::~Socket() {
}


int Socket::getServFd() const {
	return serv_fd;
}

void Socket::setServFd(int fd) {
	serv_fd = fd;
}

struct sockaddr_in Socket::getServAddr() const {
	return serv_addr;
}

void Socket::setServAddr(int sin_family, int sin_port, int s_addr) {
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = sin_family;
	serv_addr.sin_port = sin_port;
	serv_addr.sin_addr.s_addr = s_addr;
}

bool Socket::servBindAndListen() {
	while (::bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		cout << "ircserv: failed to socket bind. retrying..." << endl;
		sleep(3);
	}
	if (listen(serv_fd, MAX_CONN) == -1) {
		cout << "ircserv: failed to socket listen" << endl;
		close(serv_fd);
		return false;
	}

	poll_fd[0].fd = serv_fd;
	poll_fd[0].events = POLLIN;
	poll_fd[0].revents = 0;
	ip_addr[0] = inet_ntoa(serv_addr.sin_addr);

	for (int i = 1; i < MAX_CONN; i++){
		poll_fd[i].fd = -1;
		poll_fd[i].revents = 0;
		ip_addr[i].clear();
		port[i] = 0;
	}
	return true;
}

bool Socket::servPoll() {
	if (poll(poll_fd, MAX_CONN, -1) <= 0) {
		cout << "ircserv: poll error" << endl;
		return false;
	}
	return true;
}

void Socket::setNewPoll(Server &serv) {
	int conn_fd;
	struct sockaddr_in conn_socket;
	socklen_t addr_size;

	if (poll_fd[0].revents & POLLIN) {
		for (int i = 1; i < MAX_CONN; i++) {
			if (poll_fd[i].fd == -1) {
				conn_fd = accept(serv_fd, (struct sockaddr *)&conn_socket, &addr_size);
				poll_fd[i].fd = conn_fd;
				poll_fd[i].events = POLLIN | POLLOUT;
				poll_fd[i].revents = 0;
				ip_addr[i] = inet_ntoa(conn_socket.sin_addr);
				port[i] = conn_socket.sin_port;
				serv.createUser(wr_buf[i], poll_fd[i], ip_addr[i], port[i]);
				fcntl(poll_fd[i].fd, F_SETFL, O_NONBLOCK);
				wr_buf[i] = ":irc.local NOTICE * :*** Looking up your hostname...\r\n";
				break;
			}
		}
		poll_fd[0].revents = 0;
	}
}

void Socket::socketPolling(Server &serv, Command &command) {
	for (int i = 1; i < MAX_CONN; i++) {
		if (poll_fd[i].fd != -1) {
			if (poll_fd[i].revents & POLLHUP) {
				User* user = serv.getUser(ip_addr[i], port[i]);
				if (user)
					serv.userQuit(user);
				removePoll(i);
				continue;
			}
			if (((poll_fd[i].revents & POLL_OUT) == 0) && (poll_fd[i].revents & POLLIN))
				receivePoll(i, serv, command);
			if (wr_buf[i].length() != 0)
				sendPoll(i);
		}
	}
}


void Socket::removePoll(int idx) {
	close(poll_fd[idx].fd);
	poll_fd[idx].fd = -1;
	ip_addr[idx].clear();
	port[idx] = 0;
	rd_buf[idx].clear();
	wr_buf[idx].clear();
}

void Socket::receivePoll(int idx, Server &serv, Command &command) {
	char buf[BUFFER_SIZE] = {0, };
	ssize_t rd = read(poll_fd[idx].fd, buf, BUFFER_SIZE - 1);
	rd_buf[idx] += string(buf);
	size_t nl_idx = rd_buf[idx].find('\n');
	if (rd == 0 || nl_idx == rd_buf[idx].npos)
		return;
	poll_fd[idx].revents &= (POLLIN ^ 0xFFFF);
	User* sender = serv.getUser(ip_addr[idx], port[idx]);
	while (nl_idx != rd_buf[idx].npos && !rd_buf[idx].empty()) {
		if (!command.find_command(sender, rd_buf[idx].substr(0, nl_idx + 1))) {
			removePoll(idx);
			break;
		}
		rd_buf[idx].erase(0, nl_idx + 1);
		nl_idx = rd_buf[idx].find('\n');
	}
}

void Socket::sendPoll(int idx) {
	ssize_t len = write(poll_fd[idx].fd, wr_buf[idx].c_str(), wr_buf[idx].length());
	if (len < 0) {
		removePoll(idx);
		return;
	}
	wr_buf[idx] = wr_buf[idx].erase(0, len);
	if (wr_buf[idx].length() == 0)
		poll_fd[idx].revents &= (POLLOUT ^ 0xFFFF);
}
