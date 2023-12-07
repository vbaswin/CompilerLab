#include <stdio.h>
#include <string.h>

char stack[20];
int stackTop = -1;

typedef struct prod {
	char left;
	char right[20];
	int length;
} prod;

int checkProductions(int n, prod prodns[n]) {
	for (int i = 0; i < n; ++i) {
		int progress = stackTop;
		int j;
		for (j = prodns[i].length - 1; j >= 0; --j) {
			if (stack[progress--] != prodns[i].right[j])
				break;
		}
		if (j < 0)
			return i;
	}
	return -1;
}

void shiftReduce(int n, prod prodns[n], char *input) {
	if (*input == '\0') {
		printf("Empty input\n");
		return;
	}
	char startSymbol = prodns[0].left;
	stack[++stackTop] = *(input++);
	stack[stackTop + 1] = '\0';
	printf("%s\t\t%s\t\tShift %c\n", stack, input, *(input - 1));

	int prod;
	while (1) {
		if (stackTop == 0 && stack[stackTop] == startSymbol && (*input) == '\0') {
			// printf("%s\t%s\tReduce %c->%s\n", stack, input, prodns[prod].left, prodns[prod].right);
			printf("\nString Accepted!!\n");
			return;
		}
		prod = checkProductions(n, prodns);

		if (prod == -1 && *input == '\0') {
			printf("\nString not accepted!!\n");
			return;
		}
		if (prod != -1) {
			// reduce
			stackTop = (stackTop + 1) - prodns[prod].length;
			stack[stackTop] = prodns[prod].left;
			stack[stackTop + 1] = '\0';
			printf("%s\t\t%s\t\tReduce %c->%s\n", stack, input, prodns[prod].left, prodns[prod].right);
		} else {
			stack[++stackTop] = *(input++);
			stack[stackTop + 1] = '\0';
			printf("%s\t\t%s\t\tShift %c\n", stack, input, *(input - 1));
		}
	}
}

int main() {
	// freopen("c.in", "r", stdin);
	int n;
	printf("Enter no of productions: ");
	scanf("%d", &n);

	char inputStr[20], *input;

	prod prodns[n];

	printf("Enter productions\n");
	for (int i = 0; i < n; ++i) {
		// The space before %c in the format string is used to consume any leading whitespace characters (such as newline characters) left in the input buffer
		scanf(" %c->%s", &prodns[i].left, prodns[i].right);
		prodns[i].length = strlen(prodns[i].right);
	}

	printf("Enter input String: ");
	scanf("%s", inputStr);
	printf("\n");
	input = inputStr;

	// just to check
	// stack[++stackTop] = *input;
	// stack[0] = 'i';
	// stackTop = 0;

	// printf("Prod: %d\n", checkProductions(n, prodns));
	shiftReduce(n, prodns, input);

	return 0;
}
