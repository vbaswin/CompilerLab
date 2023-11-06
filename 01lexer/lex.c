#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char *keywords[] = {"if", "else", "int", "char", "bool", "display"};
const char *operators[] = {"+", "-", "*", "/", "=", "=="};
const char *specialSymbols[] = {"(", ")", "{", "}", "[", "]", ";", ":", ".", ","};
int noOfKeywords = 6;
int noOfOperators = 5;
int noOfSpecialSymbols = 10;

void recognizeToken(char *curToken, int sz) {
	printf("%s", curToken);
	if (sz < 4)
		printf("\t\t");
	else if (sz < 8)
		printf("\t");

	printf("\t\t");
	for (int i = 0; i < noOfKeywords; ++i) {
		if (!strcmp(curToken, keywords[i])) {
			printf("Keyword\n");
			return;
		}
	}
	for (int i = 0; i < noOfOperators; ++i) {
		if (!strcmp(curToken, operators[i])) {
			printf("Operator\n");
			return;
		}
	}
	for (int i = 0; i < noOfSpecialSymbols; ++i) {
		if (!strcmp(curToken, specialSymbols[i])) {
			printf("specialSymbol\n");
			return;
		}
	}
	if (curToken[0] == '\"') {
		printf("String\n");
		return;
	}

	printf("Identifier\n");
}

void lexParser(char *line, int sz) {
	char *curToken = (char *)malloc(100);
	int len = 0;
	int stringState = 0;
	for (int i = 0; i < sz; ++i) {
		if (line[i] == '\"' && stringState) {
			recognizeToken(curToken, len);
			len = 0;
			stringState = 0;
			continue;
		} else if (line[i] == '\"') {
			curToken[len++] = line[i];
			stringState = 1;
			continue;
		} else if (line[i] == ' ' || line[i] == '\t') {
			curToken[len] = '\0';
			if (len == 0)
				continue;

			// printf("Inside loop: %s\n", curToken);
			recognizeToken(curToken, len);
			len = 0;
			continue;
		}
		curToken[len++] = line[i];
	}
	recognizeToken(curToken, len);

	free(curToken);
}

int main() {
	FILE *fp = fopen("input.asw", "r");

	if (!fp) {
		printf("Failure\n");
		return 0;
	}

	size_t sz = 100;
	char *line = (char *)malloc(sz);

	int noOfChar;
	while ((noOfChar = getline(&line, &sz, fp)) != -1) {
		--noOfChar;
		line[noOfChar] = '\0';
		// lexParser(line, noOfChar);
		printf("%s %d\n", line, noOfChar);
		// printf("\n");
	}


	free(line);

	fclose(fp);
}
