#include <stdio.h>

#include "cli.h"
#include "file.h"
#include "level.h"

void print_greeting() {
	printf("\tAsteroids! level editor");
}

void print_options() {
	char option[20];
	printf("\n\nChoose option:");
	for (int i = 0; i < OPTION_NUM; i++) {
		sprintf_s(option, 20, "%d. %s", i + 1, OPTIONS[i].message);
		printf("\n\t%s", option);
	}
}

int get_option_from_user() {
	int option;
	bool cond;

	do {
		printf("\nOption: ");
		scanf_s("%d%*c", &option);
		cond = 1 <= option && option <= OPTION_NUM;

		if (!cond) {
			printf("You should print number from 1 to %d\n", OPTION_NUM);
		}
	} while (!cond);

	return OPTIONS[option-1].option;
}

void set_path(FileData& file_data) {
	bool cond;
	char path[120];

	do {
		printf("Path: ");
		fgets(path, 120, stdin);
		cond = load_path(path, file_data);

		if (!cond) {
			printf("Put path without \\ character and use / instead\n\n");
		}
	} while (!cond);
}

void set_filename(FileData& file_data) {
	char filename[120];

	printf("Filename: ");
	fgets(filename, 120, stdin);
	load_filename(filename, file_data);

	printf("\nFilename that setted: %s", file_data.filename);
}

void quit(bool& run) {
	run = false;
	printf("\nQuiting from level editor!");
}

void loop() {
	FileData file_data;
	//const char* filename = "filename_one";
	bool run = true;

	while (run) {
		print_options();
		int option = get_option_from_user();

		switch (option)
		{
		case SET_PATH:     set_path(file_data);     break;
		case SET_FILENAME: set_filename(file_data); break;
		case EDIT_LEVEL:   edit_level(file_data);   break;
		case QUIT:         quit(run);               break;
		}

		printf("\nFilename in end of the loop: %s", file_data.filename);
	}
}
