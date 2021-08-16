#include "lib.cpp"
#include <iostream>
#include <cstring>
#include <string.h>

int main(int argc, char* argv[]) {
	if(argc < 2) {
		std::cout << "Usage: " << argv[0] << " [options] <length>" << std::endl;
		return 1;
	}
	int len = atoi(argv[1]);
	std::string string = generateRandomString(len);
	std::cout << string << std::endl;
	return 0;
}
