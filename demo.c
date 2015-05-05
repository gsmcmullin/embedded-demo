#include <stdio.h>

int main(void)
{
	int counter = 0;

	/* Initialise semihosting file descriptors. */
	extern void initialise_monitor_handles(void);
	initialise_monitor_handles();

	while (1) {
		int a, b;
		printf("Iteration %d\n", ++counter);
		printf("Give me two numbers to add.\n");
		scanf("%d %d", &a, &b);
		printf("%d + %d = %d\n\n", a, b, a + b);
	}
	return 0;
}

