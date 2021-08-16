#include <iostream>
//#include <ifstream>
#include <fstream>
int main(int argc, char* argv[]) {
  std::ifstream infile;
  if(argc < 2) {
    std::cout << "Usage: " << argv[0] << " <filepath>" << std::endl;
    return 0;
  }
  char* filePath = argv[1];
  infile.open(filePath);
  char inCache[500];
  while(true) {
    infile >> inCache;
    std::cout << inCache << std::flush;
  }
  infile.close();
  return 0;
}
