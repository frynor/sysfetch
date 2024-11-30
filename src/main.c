#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>
#include "clarg.h"

void crossPlatformGPU(char* buffer, size_t size) {
	FILE *file = popen("lspci | grep -i 'vga'", "r");
	if (file == NULL) {
		perror("Failed to open GPU file!\n");
		return;
	}

	char gpu_name[128] = {0};

	if (fgets(buffer, size, file) != NULL) {
		char *start = strchr(buffer, '[');
		char *end = strchr(buffer, ']');
		
		if (start && end) {
			strncpy(gpu_name, start + 1, end - start - 1);
			gpu_name[end - start - 1] = '\0';

			printf("\033[32mGPU:\033[0m \033[34m%s\033[0m\n", gpu_name);
			printf("-----------------------\n\n");
		} else {
			printf("Could not parse GPU name\n");
		}
	}

	pclose(file);
}


void soundInfo(char* buffer, size_t size) {
	FILE *file = fopen("/proc/asound/version", "r");
	if (file == NULL) {
		perror("Failed to open /proc/asound/version!\n");
		return;
	}

	while (fgets(buffer, size, file)) {
		printf("\033[32mSound Version:\033[0m \033[34m%s\033[0m", buffer);
	}
}

void systemInfo() {
	struct utsname system_info;

	if (uname(&system_info) != 0) {
		perror("Failed to create utsname struct!\n");
		exit(EXIT_FAILURE);
	}

	char* username = getlogin();
	if (username != NULL) {
		printf("\n\033[34m%s\033[0m@\033[34m%s\033[0m\n", username, system_info.nodename);
	}

	printf("-----------------------\n");
	printf("\033[32mSystem:\033[0m \033[34m%s\033[0m\n", system_info.sysname);
	printf("\033[32mMachine:\033[0m \033[34m%s\033[0m\n", system_info.machine);

}

void uptimeInfo() {
	FILE *file = fopen("/proc/uptime", "r");

	if (file == NULL) {
		perror("Failed to open /proc/uptime file!\n");
		return;
	}

	double total_uptime;
	if (fscanf(file, "%lf", &total_uptime) == 1) {
		int hours = (int)total_uptime / 3600;
		int minutes = ((int)total_uptime % 3600) / 60;
		int seconds = (int)total_uptime % 60;
		
		printf("\033[32mSystem Uptime:\033[0m \033[34m%d hours, %d minutes, %d seconds\033[0m\n", hours, minutes, seconds);
	}

	fclose(file);
}

void memInfo(char* buffer, size_t size) {
	FILE *file = fopen("/proc/meminfo", "r");
	if (file == NULL) {
		perror("Failed to open /proc/meminfo file!\n");
		return;
	}

	int sizeFree = 0;
	int sizeTotal = 0;
	int sizeBuffers = 0;
	int sizeCached = 0;
	
	while (fgets(buffer, size, file) != NULL) {
		char* mem_total = strstr(buffer, "MemTotal:");
		if (mem_total != NULL) {
			mem_total += strlen("MemTotal:");

			while (*mem_total == ' ') {
				mem_total++;
			}

			char* mem_total_end = strchr(mem_total, ' ');
			if (mem_total_end != NULL) {
				*mem_total_end = '\0';
			}
			sscanf(mem_total, "%d", &sizeTotal);
			sizeTotal /= 1024;
		}

		char* mem_free = strstr(buffer, "MemFree:");
		if (mem_free != NULL) {
			mem_free += strlen("MemFree:") + 1;

			while (*mem_free == ' ') {
				mem_free++;
			}

			char* mem_free_end = strchr(mem_free, ' ');
			if (mem_free_end != NULL) {
				*mem_free_end = '\0';
			}
			sscanf(mem_free, "%d", &sizeFree);	
			sizeFree /= 1024;
		}

		char* buffers = strstr(buffer, "Buffers:");
		if (buffers != NULL) {
			buffers += strlen("Buffers:") + 1;

			while (*buffers == ' ') {
				buffers++;
			}

			char* buffers_end = strchr(buffers, ' ');
			if (buffers_end != NULL) {
				*buffers_end = '\0';
			}
			sscanf(buffers, "%d", &sizeBuffers);
			sizeBuffers /= 1024;
		}

		char* cached = strstr(buffer, "Cached:");
		if (cached != NULL && (cached == buffer || *(cached - 1) == '\n')) {
			if (strncmp(cached, "SwapCached:", strlen("SwapCached:")) != 0) {
				cached += strlen("Cached:");
				
				while (*cached == ' ') {
					cached++;
				}
				
				char* endptr;
				long int tempCached = strtol(cached, &endptr, 10);

				if (cached != endptr) {
					sizeCached = (int) (tempCached / 1024);
				}
			}
		}
	}
	int total = sizeTotal - sizeCached - sizeBuffers - sizeFree;
	printf("\033[32mMemory:\033[0m \033[34m%dMiB / %dMiB\033[0m\n", total, sizeTotal);
	fclose(file);
}


void linuxInfo(char* buffer, size_t size) {
	FILE *file = fopen("/proc/version", "r");
	if (file == NULL) {
		perror("Failed to open /proc/version file!\n");
		return;
	}
	
	if (fgets(buffer, size, file) != NULL) {
		char* version_start = strstr(buffer, "version");
		if (version_start != NULL) {
			version_start += strlen("version") + 1;

			char* version_end = strchr(version_start, ' ');
			if (version_end != NULL) {
				*version_end = '\0';
			}

			printf("\033[32mKernel:\033[0m \033[34m%s\033[0m\n", version_start);
		}
	}


	fclose(file);
}


void cpuInfo(char* buffer, size_t size) {
	FILE *file = fopen("/proc/cpuinfo", "r");
	if (file == NULL) {
		perror("Failed to open the /proc/cpuinfo file!\n");
		return;
	}

	while (fgets(buffer, size, file)) {
		if (strncmp(buffer, "model name", 10) == 0) {
			char *model_name = strchr(buffer, ':');
		       	if (model_name != NULL) {
				printf("\033[32mCPU:\033[0m \033[34m%s\033[0m", model_name + 2);
			}
			break;	
		}	
	}
	
	fclose(file);
}

int main(int argc, char *argv[]) {
	SystemConfig config;

	parse_arguments(argc, argv, &config);

	size_t size = 256;
	char buffer[size];

	systemInfo();
	if (config.show_kernel) {
		linuxInfo(buffer, size);
	}
	if (config.show_memory) {
		memInfo(buffer, size);
	}
	if (config.show_uptime) {
		uptimeInfo();
	}
	if (config.show_sound) {
		soundInfo(buffer, size);
	}
	if (config.show_cpu) {
		cpuInfo(buffer, size);
	}
	if (config.show_gpu) {
		crossPlatformGPU(buffer, size);
	}

	/* systemInfo();
	linuxInfo(buffer, size);
	memInfo(buffer, size);
	cpuInfo(buffer, size);
	gpuInfo(buffer, size);
	uptimeInfo();
	soundInfo(buffer, size); */

	return 0;
	

}
