#include <stdio.h>
#include <string.h>

typedef struct prod {
	char left;
	char right[20];
	int length;
} prod;

typedef struct firstValue {
	char nonTerminal;
	char first[20];
	int firstLen;
} firstValue;

typedef struct followValue {
	char nonTerminal;
	char follow[20];
	int followLen;
} followValue;

void display(int n, prod prodns[n]);
void displayFirstFollow(int noOfNonTerminals, firstValue firstValues[]);

int checkTerminal(char ch, int noOfNonTerminals, char nonTerminals[]) {
	for (int i = 0; i < noOfNonTerminals; ++i) {
		if (nonTerminals[i] == ch)
			return 0;
	}
	return 1;
}

void clearDone(int len, int done[]) {
	memset(done, 0, sizeof(int) * len);
}

void firstRecursive(int n, prod prodns[], int noOfNonTerminals, firstValue firstValues[], char nonTerminals[], int curProd, int curNonTerminal, int prodnsDone[]) {
	char ch = prodns[curProd].right[0];

	if (checkTerminal(ch, noOfNonTerminals, nonTerminals)) {
		// int len = firstValues[curNonTerminal].firstLen;

		firstValues[curNonTerminal].first[++firstValues[curNonTerminal].firstLen] = ch;
		// printf("Hello\n");
		prodnsDone[curProd] = 1;
		return;
	}



	// printf("%c %c %d\n", prodns[curProd].right[0], firstValues[curNonTerminal].first[len - 1], firstValues[curNonTerminal].firstLen);
}

void first(int n, prod prodns[], int noOfNonTerminals, firstValue firstValues[], char nonTerminals[]) {
	int prodnsDone[n];
	clearDone(n, prodnsDone);


	for (int i = 0; i < noOfNonTerminals; ++i) {
		int nonTerm = firstValues[i].nonTerminal;

		for (int j = 0; j < n; ++j) {
			if (prodns[j].left == nonTerm) {
				firstRecursive(n, prodns, noOfNonTerminals, firstValues, nonTerminals, j, i, prodnsDone);
			}
		}
	}

	// for (int i = 0; i < n; ++i)
	// printf("%d\n", prodnsDone[i]);

	// 	int curProd = 7;
	// 	firstRecursive(n, prodns, noOfNonTerminals, firstValues, nonTerminals, 2, 1);
	// 	firstRecursive(n, prodns, noOfNonTerminals, firstValues, nonTerminals, 6, 4);
	// 	firstRecursive(n, prodns, noOfNonTerminals, firstValues, nonTerminals, curProd, 4);
}

int main() {
	freopen("c.in", "r", stdin);

	int n;
	printf("Enter no of productions: ");
	scanf("%d", &n);

	prod prodns[n];

	printf("Enter productions, epsilon is represented by '#'\n");
	for (int i = 0; i < n; ++i) {
		// The space before %c in the format string is used to consume any leading whitespace characters (such as newline characters) left in the input buffer
		scanf(" %c->%s", &prodns[i].left, prodns[i].right);
		prodns[i].length = strlen(prodns[i].right);
	}

	// display(n, prodns);

	// initialize array of first and follows
	firstValue firstValues[n];
	followValue followValues[n];

	char ch = prodns[0].left;

	firstValues[0].nonTerminal = ch;
	followValues[0].nonTerminal = ch;

	firstValues[0].firstLen = -1;
	followValues[0].followLen = -1;

	char nonTerminals[20];
	nonTerminals[0] = ch;

	int noOfNonTerminals = 1;

	for (int i = 1; i < n; ++i) {
		int j;
		for (j = 0; j < i; ++j) {
			if (prodns[j].left == prodns[i].left)
				break;
		}
		if (j < i)
			continue;

		char ch = prodns[i].left;

		nonTerminals[noOfNonTerminals] = ch;
		firstValues[noOfNonTerminals].nonTerminal = ch;
		followValues[noOfNonTerminals].nonTerminal = ch;

		firstValues[noOfNonTerminals].firstLen = -1;
		followValues[noOfNonTerminals++].followLen = -1;
	}

	// printf("%s\n", nonTerminals);

	// for (int i = 0; i < noOfNonTerminals; ++i)
	// printf("%c %d %c %d\n", firstValues[i].nonTerminal, firstValues[i].firstLen, followValues[i].nonTerminal, followValues[i].followLen);

	// printf("%d\n", checkTerminal('(', noOfNonTerminals, nonTerminals));

	// firstValues[4].first[0] = '(';
	// firstValues[4].first[1] = 'i';

	// firstValues[4].firstLen = 1;

	first(n, prodns, noOfNonTerminals, firstValues, nonTerminals);

	displayFirstFollow(noOfNonTerminals, firstValues);
	return 0;
}

void display(int n, prod prodns[n]) {
	for (int i = 0; i < n; ++i) {
		// The space before %c in the format string is used to consume any leading whitespace characters (such as newline characters) left in the input buffer
		printf("%c->%s %d", prodns[i].left, prodns[i].right, prodns[i].length);
	}
}

void displayFirstFollow(int noOfNonTerminals, firstValue firstValues[]) {
	for (int i = 0; i < noOfNonTerminals; ++i) {
		printf("%c\t\t{ ", firstValues[i].nonTerminal);
		int len = firstValues[i].firstLen;
		if (len == -1) {
			printf(" }\n");
			continue;
		}
		for (int j = 0; j < len; ++j)
			printf("%c, ", firstValues[i].first[j]);
		printf("%c }\n", firstValues[i].first[len]);
	}
}
