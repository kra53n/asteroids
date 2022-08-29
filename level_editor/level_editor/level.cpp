#include <stdio.h>

#include "cli.h"
#include "file.h"

#define MAX_STRING_LEN 120

char* join_path_with_filename(FileData& file_data) {
	char filename[MAX_STRING_LEN];

	if (file_data.path) {
		sprintf_s(filename, MAX_STRING_LEN, "%s", file_data.filename);
		return filename;
	}

	sprintf_s(filename, MAX_STRING_LEN, "%s/%s", file_data.path, file_data.filename);
	return filename;
}

void edit_level(FileData& file_data) {
	if (!file_data.filename) {
		printf("\nFill filename");
		return;
	}

	char* filename = join_path_with_filename(file_data);
	printf("\nfilename: %s", filename);

	FILE* f;
	if (fopen_s(&f, filename, "r")) {
		printf("File doesn't exsit. ");
	}
}