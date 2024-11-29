#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "clarg.h"

void print_usage(char *program_name) {
	fprintf(stderr, "Usage: %s [options]\n", program_name);
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "  --no-cpu        Disable CPU information\n");
	fprintf(stderr, "  --no-memory     Disable memory information\n");
	fprintf(stderr, "  --no-gpu        Disable GPU information\n");
	fprintf(stderr, "  --no-sound      Disable sound information\n");
	fprintf(stderr, "  --no-uptime     Disable uptime information\n");
	fprintf(stderr, "  --no-system     Disable system information\n");
	fprintf(stderr, "  --no-kernel     Disable kernel information\n");
	fprintf(stderr, "  --help          Display this help message\n");
}

void parse_arguments(int argc, char* argv[], SystemConfig *config) {
	config->show_cpu = 1;
	config->show_gpu = 1;
	config->show_sound = 1;
	config->show_memory = 1;
	config->show_uptime = 1;
	config->show_system = 1;
	config->show_kernel = 1;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--no-cpu") == 0) {
			config->show_cpu = 0;
		} else if (strcmp(argv[i], "--no-memory") == 0) {
			config->show_memory = 0;
		} else if (strcmp(argv[i], "--no-gpu") == 0) {
			config->show_gpu = 0;
		} else if (strcmp(argv[i], "--no-sound") == 0) {
			config->show_sound = 0;
		} else if (strcmp(argv[i], "--no-uptime") == 0) {
			config->show_uptime = 0;
		} else if (strcmp(argv[i], "--help") == 0) {
			print_usage(argv[0]);
			exit(EXIT_SUCCESS);
		} else if (strcmp(argv[i], "--no-system") == 0) {
			config->show_system = 0;
		} else if (strcmp(argv[i], "--no-kernel") == 0) {
			config->show_kernel = 0;
		} else {
			fprintf(stderr, "Unkown option: %s\n", argv[i]);
			print_usage(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
}
