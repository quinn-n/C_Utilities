/*
 * Written by Quinn Neufeld <Quinn Neufeld@gmail.com>
 * 
 * Converts given integers into unicode characters.
 */
#include <iostream>
int main(int argc, char* argv[]) {
	if(argc < 2) {
		std::cout << "Usage: " << argv[0] << " <numbers>" << std::endl;
		std::cout << "Will lookup numbers on the unicode table." << std::endl;
		return 0;
	}
	for(int i=1;i < argc;i++) {
		std::cout << argv[i] << " turns into " << (char) atoi(argv[i]) << std::endl;
	}
	return 0;
}
