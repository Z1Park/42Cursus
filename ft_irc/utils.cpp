#include "ircserv.hpp"

vector<string> string_split(string str, string delimiter) {
	vector<string> vec;
	string temp;
	size_t idx;

	idx = 0;
	while (idx != string::npos) {
		idx = str.find_first_of(delimiter, 0);
		temp = str.substr(0, idx);
		if (temp != "")
			vec.push_back(temp);
		str.erase(0, idx + 1);
	}
	return vec;
}

string ulToString(size_t num) {
	string str;

	if (num == 0)
		return "0";
	while (num > 0) {
		str = static_cast<char>(num % 10 + '0') + str;
		num /= 10;
	}
	return str;
}

long long stringToll(string str) {
	unsigned long long num = 0;
	int sign = 1;
	size_t i = 0;

	if (str[i] == '-' || str[i] == '+') {
		sign *= (str[i] == '-') ? -1 : 1;
		i++;
	}
	for (; i < str.length(); i++) {
		if (isdigit(str[i]) == 0)
			break;
		num = num * 10 + static_cast<unsigned long long>(str[i]) - '0';
		if (num > 9223372036854775807)
			return -1;
	}
	return (num * sign);
}

bool check_wildcard_match(string wildcard, string str) {
	vector<string> str_vec;
	string temp;
	bool wildcard_flag = false;

	while (wildcard.length() != 0) {
		size_t idx = wildcard.find_first_of('*', 0);
		if (idx == 0) {
			str_vec.push_back("*");
			wildcard.erase(0, wildcard.find_first_not_of('*', 0));
			continue;
		}
		temp = wildcard.substr(0, idx);
		str_vec.push_back(temp);
		wildcard.erase(0, idx);
	}

	size_t idx = 0;
	for (vector<string>::iterator it = str_vec.begin(); it != str_vec.end(); it++) {
		if (wildcard_flag) {
			wildcard_flag = false;
			while (idx + (*it).length() <= str.length() && *it != str.substr(idx, (*it).length()))
				idx++;
			if (idx + (*it).length() > str.length())
				return false;
			idx += (*it).length();
		}
		else {
			if (*it == "*")
				wildcard_flag = true;
			else {
				if (str.substr(idx, (*it).length()) != *it)
					return false;
				idx += (*it).length();
			}
		}
	}
	return true;
}

bool is_needed_param(char mode, param_t &param, char flag) {
	if ((flag == '+' && string("ovlk").find(mode) == string::npos)
		|| (flag == '-' && string("ov").find(mode) == string::npos))
		return false;
	switch (mode) {
		case 'o':
			param.comment = "op";
			param.syntax = "nick";
			break;
		case 'v':
			param.comment = "voice";
			param.syntax = "nick";
			break;
		case 'l':
			param.comment = "limit";
			param.syntax = "limit";
			break;
		case 'k':
			param.comment = "key";
			param.syntax = "key";
			break;
		default:
			return false;
	}
	return true;
}

channel_mode_t make_ch_mode(char mode, string param) {
	channel_mode_t res;

	res.mode = mode;
	if (mode == 'l')
		res.param = ulToString(stringToll(param));
	else if (mode == 'k' && param.length() > 32)
		res.param = param.substr(0, 32);
	else
		res.param = param;
	return res;
}

bool find_mode(vector<channel_mode_t> &modes, channel_mode_t ch_mode) {
	vector<channel_mode_t>::iterator it;
	for (it = modes.begin(); it != modes.end(); it++) {
		if ((*it).mode == ch_mode.mode && (*it).param == ch_mode.param)
			return true;
	}
	return false;
}

vector<channel_mode_t> parse_mode(Server &serv, User *sender, vector<string> &line_vec, char flag) {
	vector<channel_mode_t> modes;
	channel_mode_t ch_mode;
	size_t mode_idx = 0;
	if (line_vec[1][0] == '+' || line_vec[1][0] == '-')
		mode_idx = 1;

	param_t param;
	param.channel_name = line_vec[0];
	param.indicator = line_vec.size();
	param.match_idx = 2;
	for (; mode_idx < line_vec[1].length(); mode_idx++) {
		param.mode = line_vec[1][mode_idx];
		try {
			checkError(serv, sender, ERR_UNKNOWNMODE, param);
			if (is_needed_param(line_vec[1][mode_idx], param, flag)) {
				checkError(serv, sender, ERR_SPECIFYPARAM, param);
				param.comment = line_vec[param.match_idx];
				checkError(serv, sender, ERR_INVALIDPARAM, param);
				ch_mode = make_ch_mode(line_vec[1][mode_idx], line_vec[param.match_idx++]);
			}
			else
				ch_mode = make_ch_mode(line_vec[1][mode_idx], "");
			if (!find_mode(modes, ch_mode))
				modes.push_back(ch_mode);
		} catch (exception &) {}
	}
	return modes;
}

string create_modestr(User *user, Channel *channel, vector<channel_mode_t> &modes, char flag) {
	string res = ":" + user->getFormattedInfo() + " MODE " + channel->getChannelName() + " " + flag;
	vector<channel_mode_t>::iterator it;
	for (it = modes.begin(); it != modes.end(); it++)
		res += (*it).mode;
	for (it = modes.begin(); it != modes.end(); it++)
		res += " " + (*it).param;
	return res;
}

string create_banmask(string str) {
	if (str.find('!') != string::npos && str.find('@') != string::npos)
		return str;
	if (str.find('!') != string::npos)
		return str + "@*";
	if (str.find('@') != string::npos)
		return "*!" + str;
	return str + "!*@*";
}

int count_param(string data) {
	vector<string> splitted = string_split(data, " ");
	return splitted.size();
}
