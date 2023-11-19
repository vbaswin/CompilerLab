#include <stdio.h>

int E();
int Edash();
int T();
int Tdash();
int F();

int main() {
	E();

	return 0;
}

int E() {
	T();
	Edash();
}

int Edash() {
	// check +
	T();
	Edash();
}

int T() {
	F();
	Tdash();
}

int Tdash() {
	// check *
	F();
	Tdash();
	// or E
}

int F() {
	// check (
	E();
	// check )

	// or check id
}
