#include <ctime>
#include <cstdlib>
#include <iostream>
int main(int argc, char* argv[]) {
    srand(time(NULL));
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << "<choices>" << std::endl;
        return 0;
    }
    int choice = rand()%(argc-1)+1;
    std::cout << argv[choice] << std::endl;
}