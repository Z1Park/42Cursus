
#ifndef __FILE_H__
#define __FILE_H__
#include <iostream>
#include <fstream>
#include <string>

class File {
	private:
		std::ifstream in_file;
		std::ofstream out_file;

	public:
		File();
		~File();

		bool replaceString(std::string filename, std::string s1, std::string s2);
		bool printFile(std::string filename);
};

#endif
