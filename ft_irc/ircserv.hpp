#pragma once
#include "types.hpp"
#include "IrcLog.hpp"
#include "Socket.hpp"
#include "Server.hpp"
#include "Command.hpp"
#include "User.hpp"
#include "Channel.hpp"

#define BUFFER_SIZE 1024

#define GREEN "\033[1;32m"
#define WHITE "\033[0m"

#define CH_MODE_I	0x01
#define CH_MODE_K	0x02
#define CH_MODE_L	0x04
#define CH_MODE_M	0x08
#define CH_MODE_N	0x10
#define CH_MODE_P	0x20
#define CH_MODE_S	0x40
#define CH_MODE_T	0x80

#define US_MODE_I	0x01
#define US_MODE_S	0x02
#define US_MODE_W	0x04
#define US_MODE_O	0x08


void checkError(Server &serv, User* sender, t_err err_no, param_t param);
void sendResponse(Server &serv, User* sender, t_rpl rpl_no, param_t param);

vector<string> string_split(string str, string delimiter);
long long stringToll(string str);
bool check_wildcard_match(string wildcard, string str);

channel_mode_t make_ch_mode(char mode, string param);
vector<channel_mode_t> parse_mode(Server &serv, User *user, vector<string> &line_vec, char flag);
string create_modestr(User *user, Channel *channel, vector<channel_mode_t> &modes, char flag);
string create_banmask(string str);
int count_param(string data);
