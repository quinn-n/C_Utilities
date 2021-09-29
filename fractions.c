#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define HELP_MSG "Usage: fractions <num>\nConverts a decimal number to a fraction.\n"

bool isInt(double num) {
	return (num - (int) num == 0);
}

int* getFract(double num) {
	int mult = 1;
	while(!isInt(num * mult)) mult++;
	int* output = (int*) malloc(sizeof(int) * 2);
	output[0] = num * mult;
	output[1] = mult;
	return output;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf(HELP_MSG);
		return 1;
	}
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
			printf(HELP_MSG);
			return 1;
		}
	}
	double num = atof(argv[1]);
	int* output = getFract(num);
	printf("%i/%i\n", output[0], output[1]);
	return 0;
}
