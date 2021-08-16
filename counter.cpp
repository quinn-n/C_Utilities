#include <iostream>
int main(int numArgs, char* args[]){
	if(numArgs < 2){
		std::cout << "Usage: " << args[0] << " <delay>" << std::endl;
		return 0;
	}
	float timer = atof(args[1]);
	std::cout << 1/timer << std::endl;
	return 0;
}
