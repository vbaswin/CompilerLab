#include <stdio.h>

int main() {
	FILE *fp = fopen("input.asw", "r");

	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;

	while ((linelen = getline(&line, &linecap, fp)) > 0) {
		// fwrite(line, linelen, 1, stdout);
		line[--linelen] = '\0';
		printf("%d %s", linelen, line);
	}

	fclose(fp);

	return 0;
}
