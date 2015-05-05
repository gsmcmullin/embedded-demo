CFLAGS = -Wall -Wextra -g3 -O0 -MD

CSRC = demo.c
OBJ = $(CSRC:.c=.o)

demo: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

.PHONY: clean
clean:
	-rm -rf *.o demo

-include *.d

