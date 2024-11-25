#include <stdio.h>
#include <string.h>

void memInfo(char* buffer, size_t size) {
	FILE *file = fopen("/proc/meminfo", "r");
	if (file == NULL) {
		perror("Failed to open /proc/meminfo file!\n");
		return;
	}

	if (fgets(buffer, size, file) != NULL) {
		char* version_start = strstr(buffer, "MemTotal:");
		if (version_start != NULL) {
			version_start += strlen("MemTotal:") + 7;

			char* version_end = strchr(version_start, ' ');
			if (version_end != NULL) {
				*version_end = '\0';
			}

			printf("Memory: %s kB\n", version_start);
		}
	}

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

			printf("Kernel: %s\n", version_start);
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
				printf("CPU: %s", model_name + 2);
			}
			break;	
		}	
	}
	
	fclose(file);
}

int main() {
	size_t size = 256;
	char buffer[size];

	cpuInfo(buffer, size);
	linuxInfo(buffer, size);
	memInfo(buffer, size);

	return 0;
	

}
