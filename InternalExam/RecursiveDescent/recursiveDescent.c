#include <stdio.h>

char str[50];
const char *cursor;

int idx = 0;

int E();
int Edash();
int T();
int Tdash();
int F();

int main() {
	printf("Enter string: ");
	scanf("%s", str);
	cursor = str;

	if (E() && (*cursor == '\0'))
		printf("String successfully parsed\n");
	else
		printf("Error in parsing string\n");

	return 0;
}

int E() {
	printf("%-16sE -> TE'\n", cursor);
	if (T()) {
		if (Edash()) {
			return 1;
		} else
			return 0;
		return 1;
	} else
		return 0;
}

int Edash() {
	if (*cursor == '+') {
		printf("%-16sE' -> +TE'\n", cursor);
		++cursor;
		if (T()) {
			if (Edash()) {
				return 1;
			} else
				return 0;
		} else
			return 0;
	} else {
		printf("%-16sEdash -> ε\n", cursor);
		return 1;
	}
}

int T() {
	printf("%-16sT -> FTdash\n", cursor);
	if (F()) {
		if (Tdash()) {
			return 1;
		} else
			return 0;
	} else
		return 0;
}

int Tdash() {
	if (*cursor == '*') {
		printf("%-16sTdash -> *FTdash\n", cursor);
		++cursor;
		if (F()) {
			if (Tdash()) {
				return 1;
			} else
				return 0;
		} else
			return 0;
	} else {
		printf("%-16sTdash -> ε\n", cursor);
		return 1;
	}
}

int F() {
	if (*cursor == '(') {
		++cursor;
		if (E()) {
			if (cursor[idx] == ')') {
				printf("%-16sF -> (E)\n", cursor);
				++cursor;
				return 1;
			} else
				return 0;
		} else
			return 0;
	} else {
		printf("%-16sF -> i\n", cursor);
		++cursor;
		return 1;
	}
}
