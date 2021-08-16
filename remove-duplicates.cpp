#include <iostream>
#include <string>
#include <vector>

//Returns true if vect contains search.
bool contains(std::vector<std::string> vect, std::string search) {
  size_t numElements = vect.size();
  for(size_t i = 0; i < numElements; i++) {
    if(vect[i] == search) return true;
  }
  return false;
}

int main() {
  std::vector<std::string> history;
  std::string input = "";
  //Read until we're at the end of our input.
  while(!std::cin.eof()) {
    std::cin >> input;
    //If input is not in history, print it and add it to the history.
    if(!contains(history, input)) {
      history.push_back(input);
      std::cout << input << std::endl;
    }
  }
  return 0;
}
