/*
Multithreadded variant of repeat script.
Repeats a message a given number of times.
If no number of times is provided, repeats msg indefinitly.
Feb. 21, 2019
*/
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <thread>
#include <pthread.h>
#include <progutil.h>
#define HELP_MSG "Usage: repeat <msg> <[times]>\nRepeats msg a given number of times. If no number of times is given, repeats msg indefinitly.\n"

typedef char byte;

static const byte NUM_THREADS = std::thread::hardware_concurrency();

struct threadInfo_t {
	byte tid;
	byte step;
	unsigned long long times;
	char* toPrint;
};

void* worker_repeat(void* threadInf) {
	threadInfo_t* threadInfo = (threadInfo_t*) threadInf;
	byte tid = threadInfo->tid;
	byte step = threadInfo->step;
	byte times = threadInfo->times;
	char* toPrint = threadInfo->toPrint;
	//If times is zero, repeat indefinitly. Else, repeat the given number of times.
	if(times == 0) {
		while(true) {
			std::cout << toPrint << std::flush;
		}
	} else {
		for(unsigned long long i = tid; i < times; i += step) {
			std::cout << toPrint << std::flush;
		}
	}
}

int main(int argc, char* argv[]) {
	if(!checkInputs(argc, argv, 2, HELP_MSG)) return 0;
	char* toRepeat = argv[1];
	unsigned long long times = 0;
	if(argc > 2) times = atoll(argv[2]);
	pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t) * NUM_THREADS);
	threadInfo_t* threadInfo = (threadInfo_t*) malloc(sizeof(threadInfo_t) * NUM_THREADS);
	//Start every thread.
	for(byte i = 0; i < NUM_THREADS; i++) {
		threadInfo[i].tid = i;
		threadInfo[i].step = NUM_THREADS;
		threadInfo[i].times = times;
		threadInfo[i].toPrint = toRepeat;
		pthread_create(&threads[i], NULL, worker_repeat, &threadInfo[i]);
	}
	//Join every thread
	void* status;
	for(byte i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], &status);
	}
}
