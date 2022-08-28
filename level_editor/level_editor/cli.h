#pragma once

enum OptionsEnum {
	SET_PATH,
	SET_FILENAME,
	EDIT_LEVEL,
	QUIT,
};

struct OPTION_INFO {
	int        option;
	const char message[20];
};

#define OPTION_NUM 4

const OPTION_INFO OPTIONS[OPTION_NUM] = {
	{ SET_PATH,     "Set path"},
	{ SET_FILENAME, "Set filename"},
	{ EDIT_LEVEL,   "Edit level"},
	{ QUIT,         "Quit"},
};

void print_greeting();
int get_option_from_user();
void loop();
