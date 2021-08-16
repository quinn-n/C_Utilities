/*
Returns the length of a string given either through command line arguments or through stdin.
Written by Quinn Neufeld.
Nov. 7, 2018
*/
#include <iostream>
#include <string>

int main(int argc, char* argv[]){
	char buffer;
	std::string str;
	//Read from stdin if we're not given a string in the arguments
	if (argc < 2){
		while(!std::cin.eof()) {
			std::cin.get(buffer);
			if(buffer != '\0') {
				if(buffer != '\r' && buffer != '\n') {
					str += buffer;
				}
			} else {
				break;
			}
		}
	} else {
		str = argv[1];
	}
	//Output the length of the string.
	std::cout << str.length() << std::endl;
	return 0;
}
