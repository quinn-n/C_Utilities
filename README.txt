#C_Utilities
Some of my utilities programs, written in C++.
make usage:
make localinstall -- compiles programs and links them to ~/.local/bin
make install -- compiles programs and links them to /bin
make -- compiles programs and leaves the binaries in ./bin/
Note: don't be worried if the compilers crash - it means you don't have fltk installed. All of the programs not listed in the GUIs folder will still work fine. If you want to use the guis, the requirements are below.

mass_append <file> <times to append> <string to append> -- append string to file a certain number of times.
len <string> -- print the length of <string>
repeat <string> <number> -- print string number of times.
counter <number> -- counts how many loops your program will run in 1 second witha delay of number -- eg. .25 will print 1
coinFlip <number> -- flip a coin a given number of times
readFile <filepath> -- constantly reads input from a file. Useful for checking input for certain usb devices (eg. /dev/input/by-id/<device>)
convert_unicode <numbers> -- looks up given numbers on a unicode table and outputs the result.
remove-duplicates -- Reads from standard input and removes all duplicates.
fractions <num> -- converts a decimal number to a fraction.
simpleCalc <num> <op> <num> -- A command line utility to perform quick calculator operations in the command line. Eg. 2 * 6 will output 12.
convert-char <char(s)> -- converts given characters to their respective unicode numbers.
generate-random-chars <num> -- Generates a given number of characters by generating random numbers between 1 and 255. You'll probably get a bunch of garbage as an output.
remove-whitespace <file> -- Removes all whitespace characters at the end of a file.
remove-duplicate-files <dirs> -- Removes all duplicate files in a directory
remove-targeted-duplicate-files -- Scans all directories marked with -s and removes all duplicate files in directories marked with -r
crc32sum <files> -- prints out crc32 hash of all files

GUIs -- all guis require fltk to compile.
len - gets length of string and shows it.
mass_append - appends a string to a file a given number of times. Requires pthread.

lib.cpp - general purpose library.
std::string itos(int) -- converts an int to a std::string
char* itoc(int) -- converts an int to a char*
isInInt(int* array, int search) -- returns true if search is in array.
std::string getStringRange(std::string,int start, int end) -- get the contents of a string between start and end.
std::string generateRandomString(unsigned int length) -- return a pseudo-random string of a given length
void makePositive(int &num) -- ensures num is a positive integer. If it is negative, it is divided by -1.
int invertInt(int num, int max) -- inverts said number relitave to max -- eg. if num is 25 and max is 100, the function returns 75.
