#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

static void board_init(void)
{
	/* Configure system clock */
	rcc_clock_setup_in_hsi_out_48mhz();

	/* Enable peripheral clocks */
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_USART2);

	/* Setup GPIO pin for USART TX */
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
	              GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART2_TX);

	/* Setup USART */
	usart_set_baudrate(USART2, 115200);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
	usart_set_mode(USART2, USART_MODE_TX_RX);
	usart_enable(USART2);
	usart_recv(USART2);
}

int _read(int file, char *ptr, int len)
{
	int i;

	if (file != STDIN_FILENO) {
		errno = EIO;
		return -1;
	}

	for (i = 0; i < len; i++) {
		ptr[i] = usart_recv_blocking(USART2);
		usart_send_blocking(USART2, ptr[i]);
		if (ptr[i] == '\r') {
			ptr[i] = '\n';
			usart_send_blocking(USART2, ptr[i]);
			return i + 1;
		}
	}

	return i;
}

int _write(int file, const char *ptr, int len)
{
	int i;

	if (file != STDOUT_FILENO) {
		errno = EIO;
		return -1;
	}

	for (i = 0; i < len; i++) {
		if (ptr[i] == '\n')
			usart_send_blocking(USART2, '\r');
		usart_send_blocking(USART2, ptr[i]);
	}

	return i;
}

int main(void)
{
	int counter = 0;
	board_init();
	while (1) {
		int a, b;
		printf("Iteration %d\n", ++counter);
		printf("Give me two numbers to add.\n");
		scanf("%d %d", &a, &b);
		printf("%d + %d = %d\n\n", a, b, a + b);
	}
	return 0;
}

