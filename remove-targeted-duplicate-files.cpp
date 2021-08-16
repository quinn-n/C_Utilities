/*
 * remove-existing-files
 * Removes files from one set of directories that already exist in another set
 * written by Quinn Neufeld
 * May 23rd 2020
*/

#include <filesystem>
#include <iostream>
#include <list>
#include <string>
#include <cstdio>
#include <cstring>

#include <zlib.h>

class File {
public:
    uint32_t hash;
    std::string path;
    File(std::string path) {
        std::string contents = readfile(path);
        this->path = path;
        hash = crc32(0, (uint8_t*) contents.c_str(), contents.length());
    }
private:
    std::string readfile(std::string &path) {
        FILE* fi = fopen(path.c_str(), "rb");
        std::string outstr;
        while (!feof(fi))
            outstr += fgetc(fi);
        fclose(fi);
        return outstr;
    }
};

std::list<File> existingFiles;

long nFiles(std::string);
void scandir(std::string);
void removedir(std::string);

bool scannedFile(std::string);

int main(int argc, char** argv) {
    if (argc < 2 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
        std::cout << "Usage: remove-existing-files -s <scandirs> -r <rmdirs>" << std::endl;
        std::cout << "Removes files from rmdirs that already exist in scandirs" << std::endl;
        return 1;
    }
    //Search argv for scan dirs
    for (int i = 1; i < argc - 1; i++) {
        if (!strcmp(argv[i], "-s")) {
            scandir(argv[i + 1]);
            i++;
        }
    }
    //Search argv for rmdirs
    for (int i = 1; i < argc - 1; i++) {
        if (!strcmp(argv[i], "-r")) {
            removedir(argv[i + 1]);
            i++;
        }
    }
}

//Returns the number of files in a directory
long nFiles(std::string path) {
    long n = 0;
    for (auto &entry: std::filesystem::recursive_directory_iterator(path)) {
        if (entry.is_regular_file())
            n++;
    }
    return n;
}

//Scans a directory
void scandir(std::string path) {
    std::cout << "Scanning " << path << " for files" << std::endl;
    long numFiles = nFiles(path);
    long n = 0;
    for (auto fi: std::filesystem::recursive_directory_iterator(path)) {
        std::cout << "Scanning file " << n + 1 << " / " << numFiles << '\r' << std::flush;
        if (fi.is_regular_file())
            existingFiles.push_back(File(fi.path().string()));
        n++;
    }
}

//Deletes duplicates in path
void removedir(std::string path) {
    std::cout << "Removing duplicates in \"" << path << '\"' << std::endl;
    long numFiles = nFiles(path);
    long n = 0;
    for (auto fi: std::filesystem::recursive_directory_iterator(path)) {
        std::cout << "Checking file " << n + 1 << " / " << numFiles << '\r' << std::flush;
        if (!fi.is_directory() && scannedFile(fi.path().string())) {
            std::cout << "Got duplicate file at " << fi.path() << std::endl;
            std::filesystem::remove(fi.path().string());
        }
        n++;
    }
}

//Returns true if path has already been scanned
bool scannedFile(std::string path) {
    File fi(path);
    for (File efi: existingFiles) {
        if (efi.hash == fi.hash)
            return true;
    }
    return false;
}
