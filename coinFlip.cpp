#include <iostream>
#include <ctime>

int main(int numArgs, char* args[]) {
	if(numArgs < 2) {
		std::cout << "Usage: " << args[0] << " <number of times>\n";
		return 0;
	}
	unsigned long numFlips = atol(args[1]);
	unsigned long heads = 0;
	unsigned long tails = 0;
	srand(time(NULL));
	for(unsigned long i=0;i<numFlips;i++){
		int choice = rand();
		//std::cout << "got " << choice << "\n";
		int midNumber = RAND_MAX/2;
		//heads
		if(choice <= midNumber) {
			heads++;
		} else if(choice >= midNumber) {
			tails++;
		}
	}
	std::cout << "Got " << heads << " heads and " << tails << " tails.\n";
	return 0;
}
