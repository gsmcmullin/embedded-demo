#include <stdio.h>

int main(void)
{
	int counter = 0;
	while (1) {
		int a, b;
		printf("Iteration %d\n", ++counter);
		printf("Give me two numbers to add.\n");
		scanf("%d %d", &a, &b);
		printf("%d + %d = %d\n\n", a, b, a + b);
	}
	return 0;
}

