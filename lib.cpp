#include <sstream>
#include <string.h>
#include <cstring>
#include <iostream>
#include <ctime>
#include <cstdlib>

//global variables
std::string chars = "`~1!2@3#4$56^7&8*9(0)-_=+qQwWeErRtTyYuUiIoOpPaAsSdDfFgGhHjJkKlL;:'zZxXcCvVbBnNmM,<.>/?";

std::string itos(int num) {
    std::ostringstream stream;
    stream << num;
    return stream.str();
}

char* itoc(int num) {
    std::string string = itos(num);
    char* output = new char[string.length()];
    strcpy(output, string.c_str());
    return output;
}

std::string getStringRange(std::string string, int start, int end) //get parts of string from start to end.
{
    std::string outString = "";
    for(int i=start;i<end;i++) {
        outString += string[i];
    }
    return outString;
}

bool isInInt(int array[], size_t arraySize, int search)  //returns true if search is in array.
{
    for(int i=0;i<arraySize;i++) {
        if(array[i] == search) {
            return true;
        }
    }
    return false;
}

std::string deleteInString(std::string string, int start, int end) //delete the part of string from start to end.
{
    std::string cache = "";
    int strLen = string.length();
    //create array of all the numbers between start and end
    int numElements = end-start;
    int numArray[numElements];
    int counter = 0;
    for(int i=start;i<end;i++) {
        numArray[counter] = i;
        counter++;
    }
    for(int i=0;i<strLen;i++) {
        if(!isInInt(numArray,numElements,i)) {
            cache += string[i];
        }
    }
    return cache;
}

int* getIntRange(int* numbers, int start, int end) {
    int output[end-start];
    int n = 0;
    for(int i=start;i<end;i++) {
        output[n] = numbers[i];
    }
    return numbers;
}

std::string generateRandomString(unsigned int length) { //generate a random string of length length
    srand(time(NULL));
    std::string outputString = "";
    int charsLen = chars.length();
    for(unsigned int i=0;i<length;i++) {
        outputString += chars[(rand()%charsLen)];
    }
    return outputString;
}

void makePositive(int &num) {
    if(num < 0){
        num /= -1;
    }
}

int invertInt(int num, int max) {
    num /= -1;
    num += max;
    return num;
}