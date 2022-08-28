#pragma once

struct FileData {
	const char* path;
	const char* filename;
};

void load_path(const char* path);
void load_filename(const char* path);
