#include <stdio.h>
#include <string.h>

#include "file.h"

void change_symbol(const char* path, char s1, char s2) {
	for (char* sym = strchr((char*)path, s1); sym; sym = strchr(++sym, s1)) {
		*sym = s2;
	}
}

bool load_path(const char* path, FileData& file_data) {
	if (strchr(path, '\\'))
		return false;
	file_data.path = path;
	return true;
}

bool load_filename(const char* filename, FileData& file_data) {

	file_data.filename = filename;
	return true;
}
