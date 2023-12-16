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
void displayFirstFollow(int noOfNonTerminals, firstValue firstValues[], followValue followValues[]);

int checkTerminal(char ch, int noOfNonTerminals, char nonTerminals[]) {
	for (int i = 0; i < noOfNonTerminals; ++i) {
		if (nonTerminals[i] == ch)
			return i;
	}
	return -1;
}

void clearDone(int len, int done[]) {
	memset(done, 0, sizeof(int) * len);
}

void firstRecursive(int n, prod prodns[], int noOfNonTerminals, firstValue firstValues[], char nonTerminals[], int curProd, int curNonTerminal, int prodnsDone[]) {
	char ch = prodns[curProd].right[0];
	// printf("\nCurrent nonTerminal: %c\n", ch);
	int nonTerminalPos = checkTerminal(ch, noOfNonTerminals, nonTerminals);

	if (nonTerminalPos == -1) {
		firstValues[curNonTerminal].first[firstValues[curNonTerminal].firstLen++] = ch;
		firstValues[curNonTerminal].first[firstValues[curNonTerminal].firstLen] = '\0';

		prodnsDone[curProd] = 1;
		return;
	}

	for (int i = 0; i < n; ++i) {
		if (prodns[i].left == ch && !prodnsDone[i])
			firstRecursive(n, prodns, noOfNonTerminals, firstValues, nonTerminals, i, nonTerminalPos, prodnsDone);
	}

	// concat first or nonTerminalPos
	if (firstValues[nonTerminalPos].firstLen) {
		// printf("\nfirst::: %c\t%s\n", nonTerminals[nonTerminalPos], firstValues[nonTerminalPos].first);
		// printf("prev: %s\tneeded: %s\n", firstValues[curNonTerminal].first, firstValues[nonTerminalPos].first);
		// strcat(firstValues[curNonTerminal].first, firstValues[nonTerminalPos].first);
		int epsilonPresent = 0;
		for (int m = 0; m < prodns[curProd].length; ++m) {
			for (int k = 0; k < firstValues[nonTerminalPos].firstLen; ++k) {
				char firstCh = firstValues[nonTerminalPos].first[k];
				if (firstCh == '#') {
					if (!epsilonPresent)
						firstValues[curNonTerminal].first[firstValues[curNonTerminal].firstLen++] = firstCh;
					epsilonPresent = 1;
				} else {
					firstValues[curNonTerminal].first[firstValues[curNonTerminal].firstLen++] = firstCh;
				}
			}
			if (epsilonPresent) {
				if (m != (prodns[curProd].length - 1)) {
					// printf("hello\n");
					char nextCh = prodns[curProd].right[m + 1];
					nonTerminalPos = checkTerminal(nextCh, noOfNonTerminals, nonTerminals);
					// printf("hehe: %c\n", nextCh);

					int nextTerminalProd;
					for (int p = 0; p < n; ++p) {
						if (prodns[p].left == nextCh) {
							nextTerminalProd = p;
							break;
						}
					}

					firstRecursive(n, prodns, noOfNonTerminals, firstValues, nonTerminals, nextTerminalProd, nonTerminalPos, prodnsDone);
					epsilonPresent = 0;
				}
			} else
				break;
		}

		// firstValues[curNonTerminal].firstLen += firstValues[nonTerminalPos].firstLen;
		prodnsDone[curProd] = 1;
	}
}

void first(int n, prod prodns[], int noOfNonTerminals, firstValue firstValues[], char nonTerminals[]) {
	int prodnsDone[n];
	clearDone(n, prodnsDone);

	for (int i = 0; i < noOfNonTerminals; ++i) {
		int nonTerm = firstValues[i].nonTerminal;

		for (int j = 0; j < n; ++j) {
			if (prodns[j].left == nonTerm && !prodnsDone[j]) {
				firstRecursive(n, prodns, noOfNonTerminals, firstValues, nonTerminals, j, i, prodnsDone);
			}
		}
	}

	// for (int i = 0; i < n; ++i)
	// printf("%d\n", prodnsDone[i]);

	// 	int curProd = 7;
	// firstRecursive(n, prodns, noOfNonTerminals, firstValues, nonTerminals, 3, 2, prodnsDone);
	// 	firstRecursive(n, prodns, noOfNonTerminals, firstValues, nonTerminals, 6, 4);
	// 	firstRecursive(n, prodns, noOfNonTerminals, firstValues, nonTerminals, curProd, 4);
}

void followRecursive(int n, prod prodns[], int noOfNonTerminals, followValue followValues[], firstValue firstValues[], char nonTerminals[], int curNonTerminal, int followDone[]) {
	// printf("Hello %c\n", nonTerminals[curNonTerminal]);
	char ch = nonTerminals[curNonTerminal];

	if (followDone[curNonTerminal])
		return;

	int noRepeat[noOfNonTerminals];
	memset(noRepeat, 0, sizeof(int) * noOfNonTerminals);
	int nonTerminalPos;

	for (int i = 0; i < n; ++i) {
		int epsilonPresent = 0;
		for (int j = 0; j < prodns[i].length; ++j) {
			if (prodns[i].right[j] == ch || epsilonPresent) {
				if (j == prodns[i].length - 1) {
					if (ch != prodns[i].left) {
						nonTerminalPos = checkTerminal(prodns[i].left, noOfNonTerminals, nonTerminals);

						// follow has been found for left non-terminal
						if (followDone[nonTerminalPos]) {
							strcat(followValues[curNonTerminal].follow, followValues[nonTerminalPos].follow);
							followValues[curNonTerminal].followLen += followValues[nonTerminalPos].followLen;
						} else {
							followRecursive(n, prodns, noOfNonTerminals, followValues, firstValues, nonTerminals, nonTerminalPos, followDone);
							strcat(followValues[curNonTerminal].follow, followValues[nonTerminalPos].follow);
							followValues[curNonTerminal].followLen += followValues[nonTerminalPos].followLen;
						}
						noRepeat[nonTerminalPos] = 1;
					}
				} else {
					nonTerminalPos = checkTerminal(prodns[i].right[j + 1], noOfNonTerminals, nonTerminals);
					// this is a terminal
					if (nonTerminalPos == -1) {
						// printf("\nfollow::: %c\t%s\n", ch, followValues[curNonTerminal].follow);
						// printf("prev: %s\tneeded: %c\n", followValues[curNonTerminal].follow, prodns[i].right[j + 1]);
						followValues[curNonTerminal].follow[followValues[curNonTerminal].followLen++] = prodns[i].right[j + 1];
					} else {
						if (noRepeat[nonTerminalPos])
							continue;
						epsilonPresent = 0;
						for (int k = 0; k < firstValues[nonTerminalPos].firstLen; ++k) {
							char firstCh = firstValues[nonTerminalPos].first[k];
							if (firstCh == '#') {
								epsilonPresent = 1;
							} else {
								followValues[curNonTerminal].follow[followValues[curNonTerminal].followLen++] = firstCh;
							}
						}
						noRepeat[nonTerminalPos] = 1;
					}
				}
			}
		}
	}
	followDone[curNonTerminal] = 1;
}

void follow(int n, prod prodns[], int noOfNonTerminals, followValue followValues[], firstValue firstvalues[], char nonTerminals[]) {
	int followDone[noOfNonTerminals];
	clearDone(noOfNonTerminals, followDone);

	followValues[0].follow[0] = '$';
	++followValues[0].followLen;

	for (int k = 0; k < noOfNonTerminals; ++k) {
		followRecursive(n, prodns, noOfNonTerminals, followValues, firstvalues, nonTerminals, k, followDone);
	}

	// for (int i = 0; i < noOfNonTerminals; ++i)
	// printf("%d\n", followDone[i]);
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

	firstValues[0].firstLen = 0;
	followValues[0].followLen = 0;

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

		firstValues[noOfNonTerminals].firstLen = 0;
		followValues[noOfNonTerminals++].followLen = 0;
	}

	for (int i = 0; i < noOfNonTerminals; ++i) {
		memset(firstValues[i].first, '\0', 20);
		memset(followValues[i].follow, '\0', 20);
	}


	// followValues[3].follow[0] = '$';
	// ++followValues[3].followLen;

	first(n, prodns, noOfNonTerminals, firstValues, nonTerminals);

	follow(n, prodns, noOfNonTerminals, followValues, firstValues, nonTerminals);


	displayFirstFollow(noOfNonTerminals, firstValues, followValues);
	return 0;
}

void display(int n, prod prodns[n]) {
	for (int i = 0; i < n; ++i) {
		// The space before %c in the format string is used to consume any leading whitespace characters (such as newline characters) left in the input buffer
		printf("%c->%s %d", prodns[i].left, prodns[i].right, prodns[i].length);
	}
}

void displayFirstFollow(int noOfNonTerminals, firstValue firstValues[], followValue followValues[]) {
	printf("NonTerminal\tFirst\t\t\tFollow\n\n");
	for (int i = 0; i < noOfNonTerminals; ++i) {
		printf("%c\t\t{ ", firstValues[i].nonTerminal);
		int len = firstValues[i].firstLen;
		if (!len) {
			printf(" }\n");
			continue;
		}
		for (int j = 0; j < len - 1; ++j)
			printf("%c, ", firstValues[i].first[j]);
		printf("%c }", firstValues[i].first[len - 1]);


		printf("\t\t{ ");
		len = followValues[i].followLen;
		if (!len) {
			printf(" }\n");
			continue;
		}
		for (int j = 0; j < len - 1; ++j)
			printf("%c, ", followValues[i].follow[j]);
		printf("%c }\n", followValues[i].follow[len - 1]);
	}
}
