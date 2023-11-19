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
	if (sz <= 4)
		printf("\t");
	else if (sz <= 8)
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
		if (line[i] == '\"') {
			if (stringState) {
				curToken[len++] = '"';	  // ;)
				// printf("STring: %s\n", curToken);
				recognizeToken(curToken, len);
				++i;
				len = 0;
				// printf("char : %c\n", line[--i]);
				stringState = 0;
				continue;
			} else {
				curToken[len++] = line[i];
				stringState = 1;
				continue;
			}
		} else if (stringState) {
			curToken[len++] = line[i];
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
	if (len != 0) {
		curToken[len] = '\0';
		recognizeToken(curToken, len);
		len = 0;
	}
	// recognizeToken(curToken, len);

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
		// printf("%s %d\n", line, noOfChar);
		lexParser(line, noOfChar);
		printf("\n");
	}


	free(line);

	fclose(fp);
}
