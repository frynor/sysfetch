#ifndef CLARG_H
#define CLARG_H

typedef struct {
	int show_cpu;
	int show_memory;
	int show_gpu;
	int show_sound;
	int show_uptime;
	int show_system;
	int show_kernel;
} SystemConfig;

void parse_arguments(int argc, char* argv[], SystemConfig *config);

void print_usage(char *program_name);

#endif
