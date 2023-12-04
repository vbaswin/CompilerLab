#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct expression {
	char var[20];
	char operand1[20];
	char operand2[20];
	char operator;
	int flag;
} exp;

void propagate(int idx, char *var, char *val, int expNo, exp expns[expNo]);
void output(int expNo, exp expns[expNo]);

void constantPropagation(int expNo, exp expns[expNo]) {
	int change = 1;
	while (change) {
		change = 0;
		for (int i = 0; i < expNo; ++i) {
			int result = 0;
			char temp[20];

			if (expns[i].flag)
				continue;

			if ((isdigit(expns[i].operand1[0]) && isdigit(expns[i].operand2[0])) || (expns[i].operator== '=')) {
				char ch = expns[i].operator;
				int op1 = atoi(expns[i].operand1);
				int op2 = atoi(expns[i].operand2);

				switch (ch) {
				case '+':
					result = op1 + op2;
					break;
				case '-':
					result = op1 - op2;
					break;
				case '*':
					result = op1 * op2;
					break;
				case '/':
					result = op1 / op2;
					break;
				case '=':
					result = op1;
					break;
				}
				strcpy(temp, expns[i].var);
				sprintf(expns[i].var, "%d", result);
				expns[i].flag = 1;
				propagate(i, temp, expns[i].var, expNo, expns);
				change = 1;
				// output(expNo, expns);
			}
		}
	}
}

int main() {
	// freopen("c.in", "r", stdin);
	int expNo;
	printf("Enter no of exp: ");
	scanf("%d", &expNo);
	exp expns[expNo];
	for (int i = 0; i < expNo; ++i) {
		scanf("%s %s %c %s", expns[i].var, expns[i].operand1, &expns[i].operator, expns[i].operand2);
		expns[i].flag = 0;
	}

	constantPropagation(expNo, expns);

	output(expNo, expns);

	return 0;
}

void propagate(int idx, char *var, char *val, int expNo, exp expns[expNo]) {
	for (int i = 0; i < expNo; ++i) {
		if (!strcmp(expns[i].operand1, var))
			strcpy(expns[i].operand1, val);
		if (!strcmp(expns[i].operand2, var))
			strcpy(expns[i].operand2, val);
	}
}

void output(int expNo, exp expns[expNo]) {
	printf("\n\nOptimised Code\n");

	for (int i = 0; i < expNo; ++i) {
		printf("%s %s %c %s\n", expns[i].var, expns[i].operand1, expns[i].operator, expns[i].operand2);
	}
}
