#include <stdio.h>

#include "cli.h"

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
		scanf_s("%d", &option);
		cond = 1 <= option && option <= OPTION_NUM;

		if (!cond) {
			printf("You should print number from 1 to %d\n", OPTION_NUM);
		}
	} while (!cond);

	return OPTIONS[option-1].option;
}

void loop() {
	while (true) {
		print_options();
		int option = get_option_from_user();

		switch (option)
		{
		case SET_PATH:
			break;

		case SET_FILENAME:
			break;

		case EDIT_LEVEL:
			break;

		case QUIT:
			break;
		}

		break;
	}
}
