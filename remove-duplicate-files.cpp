
#include <iostream>
#include <filesystem>
#include <list>
#include <string>
#include <cstring>
#include <cstdio>
#include <zlib.h>

struct filehash {
    uint32_t hash;
    std::string filename;
};

std::list<filehash> hashes;

bool hash_exists(uint32_t hash);

std::string readfile(const char* path);

void remove_duplicates(const char* path);

void print_help();

int main(int argc, char** argv) {
    if (argc < 2 || !strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
        print_help();
        return 1;
    }
    remove_duplicates(argv[1]);
}

void print_help() {
    std::cout << "Usage: remove-duplicate-files <dir>" << std::endl;
    std::cout << "Removes all duplicate files from a directory." << std::endl;
}

//Reads the contents of a file at path and returns them in a string
std::string readfile(const char* path) {
    std::string out;
    FILE* fi = fopen(path, "rb");
    while (!feof(fi))
        out += fgetc(fi);
    fclose(fi);
    return out;
}

void remove_duplicates(const char* path) {
    for (const auto entry: std::filesystem::recursive_directory_iterator(path)) {
        if (!entry.is_directory()) {
            std::string contents = readfile(entry.path().c_str());
            uint32_t hash = crc32(0, (uint8_t*) contents.c_str(), contents.length());
            if (hash_exists(hash)) {
                std::cout << "Got duplicate files, deleting " << entry.path() << std::endl;
                std::filesystem::remove(entry.path().c_str());
            } else {
                filehash newhash;
                newhash.filename = entry.path();
                newhash.hash = hash;
                hashes.push_back(newhash);
            }
        }
    }
}

//Returns true if hash is in hashes
bool hash_exists(uint32_t hash) {
    for (filehash fhash: hashes) {
        if (fhash.hash == hash)
            return true;
    }
    return false;
}