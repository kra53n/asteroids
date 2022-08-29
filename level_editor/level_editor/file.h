#pragma once

struct FileData {
	const char* path     = 0;
	const char* filename = 0;
};

bool load_path(const char* path, FileData& file_data);
bool load_filename(const char* path, FileData& file_data);
