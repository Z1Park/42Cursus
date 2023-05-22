
#include "File.hpp"

File::File() {
}

File::~File() {
	if (in_file.is_open())
		in_file.close();
	if (out_file.is_open())
		out_file.close();
	in_file.clear();
	out_file.clear();
}


bool File::replaceString(std::string filename, std::string s1, std::string s2) {
	std::string buffer;
	std::string tmp;
	size_t i;

	in_file.open(filename);
	if (in_file.fail()) {
		std::cout << "Can not open " << filename << std::endl;
		return false;
	}
	while (!in_file.eof()) {
		if (buffer != "")
			buffer += "\n";
		getline(in_file, tmp);
		buffer += tmp;
	}
	i = 0;
	while (i < buffer.length()) {
		if (i + s1.length() < buffer.length() && s1.compare(buffer.substr(i, s1.length())) == 0) {
			buffer.erase(i, s1.length());
			buffer.insert(i, s2);
			i += s2.length();
		}
		i++;
	}
	in_file.close();
	out_file.open(filename + ".replace");
	if (out_file.fail()) {
		std::cout << "Can not open " << filename << std::endl;
		return false;
	}
	out_file << buffer;
	out_file.close();
	return true;
}

bool File::printFile(std::string filename) {
	std::string tmp;

	in_file.open(filename);
	if (in_file.fail()) {
		std::cout << "Can not open " << filename << std::endl;
		return false;
	}
	while (!in_file.eof()) {
		getline(in_file, tmp);
		std::cout << tmp << std::endl;
	}
	in_file.close();
	return true;
}
