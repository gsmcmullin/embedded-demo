CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
CPUFLAGS = -mcpu=cortex-m3 -mthumb
CFLAGS = -Wall -Wextra -g3 -O0 -MD $(CPUFLAGS)
LDFLAGS = $(CPUFLAGS)
LDLIBS = -lc -lnosys

CSRC = demo.c
OBJ = $(CSRC:.c=.o)

all: demo.hex demo.srec

demo.elf: libopencm3 $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -O srec $< $@

.PHONY: libopencm3
libopencm3:
	if [ ! -f libopencm3/Makefile ]; then \
		git submodule init; \
		git submodule update; \
	fi
	$(MAKE) -C libopencm3 lib/stm32/f1

.PHONY: clean
clean:
	-$(MAKE) -C libopencm3 clean
	-rm -rf *.o *.elf *.hex *.srec

-include *.d

