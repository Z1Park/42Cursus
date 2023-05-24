#include "ircserv.hpp"

int check_arugment(int ac, char **av, int &port) {
	string temp;

	if (ac != 3) {
		cout << "usage: ircserv <port> <password>" << endl;
		return -1;
	}
	temp = av[1];
	for (size_t i = 0; i < temp.length(); i++) {
		if (isdigit(temp[i]) == 0) {
			cout << "ircserv: wrong port number" << endl;
			return -1;
		 }
	}
	port = atoi(av[1]);
	if (port <= 0 || port >= 65535) {
		cout << "ircserv: wrong port number" << endl;
		return -1;
	}
	return 0;
}

int set_socket(Socket &sock, int port) {
	cout << "Loading core modules ...................." << endl;
	int serv_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (serv_fd == -1) {
		cout << "ircserv: failed to make server socket" << endl;
		return -1;
	}

	sock.setServFd(serv_fd);
	sock.setServAddr(AF_INET, htons(port), htonl(INADDR_ANY));
	if (!sock.servBindAndListen())
		return -1;

	return 0;
}

int main(int ac, char **av) {
	int port = 0;
	Socket sock;
	Server serv("root", inet_ntoa(sock.getServAddr().sin_addr), sock.getServAddr().sin_port);
	Command command(serv);

	if (check_arugment(ac, av, port) < 0)
		return 1;
	cout << GREEN << "ircserv - Internet Relay Chat Daemon" << WHITE << endl
		<< endl
		<< "ircserv Process ID: " << GREEN << getpid() << WHITE << endl
		<< endl;
	serv.setPassword(av[2]);
	if (set_socket(sock, port) < 0)
		return 1;
	cout << "ircserv is now running as " << serv.getServName() << " with 100 max open sockets" << endl;
	while (1) {
		if (!sock.servPoll())
			break;
		sock.setNewPoll(serv);
		sock.socketPolling(serv, command);
	}
}
