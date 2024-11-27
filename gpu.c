#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gpuInfo(char* buffer, size_t size) {
	FILE *file = fopen("/proc/driver/nvidia/gpus/0000:01:00.0/information", "r");
	
	if (file == NULL) {
		perror("Failed to open GPU file!\n");
		return;
	}
	
	while (fgets(buffer, size, file)) {
		char* model_name = strstr(buffer, "Model:");
		if (model_name != NULL) {
			model_name += strlen("Model:");
			while (*model_name == ' ') {
				model_name++;
			}

			char* model_name_end = strchr(model_name, '\n');
			if (model_name_end != NULL) {
				*model_name_end = '\0';
			}

			printf("GPU: %s\n", model_name);
		}		
	}
}

int main() {
	size_t size = 256;
	char buffer[256];

	gpuInfo(buffer, size);

	return 0;
}
