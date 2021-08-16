/*
 * crc32sum
 * prints out crc32sum of files
 * written by Quinn Neufeld
 * May 26th 2020
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include <pthread.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <zlib.h>

struct ThreadInfo {
    int tid;
    int nprocs;
    char** paths;
    int npaths;
    uint32_t* hashes;
    pthread_mutex_t* print_mutex;
};

typedef struct ThreadInfo threadinfo;

void print_help();
void* worker_thread(void*);
long fsize(FILE* fi);
void read_file(FILE* fi, char** buff);

int main(int argc, char** argv) {
    //Verify inputs
    if (argc < 2 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
        print_help();
        return 1;
    }
    char** paths = argv + 1;
    int npaths = argc - 1;
    //Spawn threads
    int nprocs = get_nprocs();
    threadinfo threadinf[nprocs];
    uint32_t hashes[argc - 1];
    pthread_t threads[nprocs];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    for (int i = 0; i < nprocs; i++) {
        threadinf[i].tid = i;
        threadinf[i].nprocs = nprocs;
        threadinf[i].paths = paths;
        threadinf[i].npaths = npaths;
        threadinf[i].hashes = &hashes;
        threadinf[i].print_mutex = &mutex;
        pthread_create(&threads[i], NULL, worker_thread, (void*) &threadinf[i]);
    }
    //Join threads
    for (int i = 0; i < nprocs; i++)
        pthread_join(threads[i], NULL);
    //Print hashes
    for (int i = 0; i < npaths; i++)
        printf("%s: %x\n", paths[i], hashes[i]);
}

//Prints help msg
void print_help() {
    printf("Usage: crc32sum <files>\n");
    printf("Prints out crc32 hash of given files.\n");
}

//Returns the size of a file
long fsize(FILE* fi) {
    long curpos = ftell(fi);
    fseek(fi, 0, SEEK_END);
    long len = ftell(fi);
    fseek(fi, curpos, SEEK_SET);
    return len;
}

//Reads a file and puts the results in buff.
void read_file(FILE* fi, char** buff) {
    //Get filesize and allocate buffer
    long n_bytes = fsize(fi);
    char* outbuf = malloc(sizeof(char) * n_bytes);
    //Read bytes from file
    for (long i = 0; i < n_bytes; i++)
        outbuf[i] = fgetc(fi);
    //Set buff
    *buff = outbuf;
}

//Hash worker thread
void* worker_thread(void* args) {
    threadinfo* tinfo = (threadinfo*) args;
    for (int i = tinfo->tid; i < tinfo->npaths; i += tinfo->nprocs) {
        if (access(tinfo->paths[i], R_OK) == -1) {
            pthread_mutex_lock(tinfo->print_mutex);
            printf("Cannot read from file %s\n", tinfo->paths[i]);
            pthread_mutex_unlock(tinfo->print_mutex);
            continue;
        }
        char* contents;
        FILE* fi = fopen(tinfo->paths[i], "rb");
        read_file(fi, &contents);
        tinfo->hashes[i] = crc32(0, (const Bytef*) contents, strlen(contents));
    }
    return NULL;
}
