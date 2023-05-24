#pragma once
#include "ircserv.hpp"

#define BOT_MSG "42 Seoul은 그동안 없었던 새로운 소프트웨어교육 프로그램 입니다. 문의:qna@innoaca.kr / 02-6177-2100\n"

class Command {
	public:
		class cmd_info {
			public:
				int min_param;
				bool register_needed;
				void (Command::*func)(User*, string);

				cmd_info(int min_param, bool register_needed, void (Command::*func)(User*, string))
					: min_param(min_param), register_needed(register_needed), func(func) {}
		};

	private:
		Server& serv;
		map<string, cmd_info> cmd_map;

		void start_connect(User &user);
		void set_nickname(User* sender,  string data);
		bool check_password(User* sender,  string data);

		void user_mode_check(User *user, vector<string> splited);
		bool set_channel_mode(Channel *channel, User *sender, channel_mode_t mode);
		bool unset_channel_mode(Channel *channel, User *sender, channel_mode_t mode);
		void send_banlist(User *sender, param_t &param);
		void mode_channel(User *sender, vector<string> line_vec);

		void set_user_info(User* sender,  string data);
		void ping_pong(User* sender,  string data);
		void join_channel(User* sender,  string data);
		void check_and_set_mode(User* sender,  string data);
		void send_who_info(User* sender,  string data);
		void send_whois_info(User* sender,  string data);
		void receive_message(User* sender,  string data);
		void invite_user(User* sender,  string data);
		void set_topic(User* sender,  string data);
		void kick_user(User* sender,  string data);
		void user_list(User* sender,  string data);
		void leave_channel(User* sender,  string data);
		void quit_client(User* sender,  string data);

	public:
		Command(Server& serv);
		~Command();
		Command& operator=(const Command& ref);

		bool find_command(User* sender, string buf);
};
