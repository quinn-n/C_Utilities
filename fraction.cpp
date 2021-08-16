
#include <iostream>
#include <pthread.h>
#include <thread>
#include <cmath>
#include <cstdlib>
#include <progutil.h>

#define ISINT_TOLERANCE .00000001

#define HELP_MSG "Usage: fraction <num>\nFinds the fraction from a decimal number.\n"

static size_t numThreads = std::thread::hardware_concurrency();

struct result_t {
    double num;
};

struct hasFound_t {
    bool hasFound;
    double foundNum;
};

struct tArgs {
    size_t tid;
    size_t numThreads;
    double num;
    result_t* result;
    hasFound_t* hasFound;
};

//Returns true if num is an integer
bool isInt(double num) {
    return (fmod(num, 1) < ISINT_TOLERANCE);
}

//Worker function to find the denominator from a fraction with a decimal number
void* fract_worker(void* thread_args) {
    tArgs* thrArgs = (tArgs*) thread_args;
    //Fill default values
    thrArgs->result->num = 0;
    for (size_t i = thrArgs->tid; i < thrArgs->hasFound->foundNum || !thrArgs->hasFound->foundNum; i += thrArgs->numThreads) {
        //If num * i is a whole number, set hasFound to true and the result number
        if (isInt(i * thrArgs->num)) {
            thrArgs->hasFound->hasFound = true;
            thrArgs->hasFound->foundNum = i;
            thrArgs->result->num = i;
        }
    }
    return NULL;
}

//Returns the denominator from a fraction with a decimal number
double getFract(double num) {
    pthread_t threads[numThreads];
    tArgs thrArgs[numThreads];
    hasFound_t* hasFound = new hasFound_t;
    hasFound->hasFound = false;
    //Fill thread arguments and spawn threads
    for (size_t i = 0; i < numThreads; i++) {
        thrArgs[i].tid = i + 1;
        thrArgs[i].numThreads = numThreads;
        thrArgs[i].num = num;
        thrArgs[i].result = new result_t;
        thrArgs[i].hasFound = hasFound;
        pthread_create(&threads[i], NULL, fract_worker, &thrArgs[i]);
    }
    //Join threads
    for (size_t i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }
    //Return smallest non-zero value from the results
    double smallest = thrArgs[0].result->num;
    for (size_t i = 0; i < numThreads; i++) {
        if (smallest == 0)
            smallest = thrArgs[i].result->num;
        if (thrArgs[i].result->num < smallest && thrArgs[i].result->num != 0)
            smallest = thrArgs[i].result->num;
    }
    return smallest;
}

int main(int argc, char** argv) {
    if (!checkInputs(argc, argv, 2, (char*) HELP_MSG))
        return 1;
    double num = atof(argv[1]);
    double denom = getFract(num);
    std::cout << num * denom << " / " << denom << std::endl;
    return 0;
}