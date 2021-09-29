#include <fstream>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>

typedef struct APPEND_ARGS {
	std::fstream *fi;
	const char* to_append;
	long times;
	int tid;
	int n_threads;
} append_args;

void append(append_args args) {
	for (long i = args.tid; i < args.times; i += args.n_threads)
		*args.fi << args.to_append;
}

int main(int argc,char* argv[]){
	if (argc < 4) {
		std::cout << "Usage: " << argv[0] << " <file> <times to append> <string to append>" << std::endl;
		return 1;
	}
	long times = atol(argv[2]);
	//Open file
	std::fstream fi;
	fi.open(argv[1], std::ios::app);
	//Spawn threads
	int n_threads = std::thread::hardware_concurrency();
	std::vector<std::thread*> threads;
	threads.resize(n_threads);
	std::vector<append_args> aargs;
	aargs.resize(n_threads);
	for (int i = 0; i < n_threads; i++) {
		aargs[i].fi = &fi;
		aargs[i].n_threads = n_threads;
		aargs[i].tid = i;
		aargs[i].times = times;
		aargs[i].to_append = argv[3];
		threads[i] = new std::thread(append, aargs[i]);
	}
	//Join threads
	for (int i = 0; i < n_threads; i++) {
		threads[i]->join();
		delete threads[i];
	}
	fi.close();
}
