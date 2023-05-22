
#ifndef __HARL_H__
#define __HARL_H__
#include <iostream>
#include <string>

class Harl {
	private:
		static void debug();
		static void info();
		static void warning();
		static void error();

	public:
		void complain(std::string level);
};

#endif
