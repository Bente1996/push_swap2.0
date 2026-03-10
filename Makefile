EXEC_NAME := push_swap
HEADERFILES := push_swap.h
SRCFILES := main.c \
	    parsing.c

OBJFILES := $(SRCFILES:.c=.o)
CFLAGS ?= -Wall -Wextra -Werror

all: $(EXEC_NAME)

run: $(EXEC_NAME)
	./$(EXEC_NAME)

$(EXEC_NAME): $(OBJFILES)
	$(CC) $(OBJFILES) $(CFLAGS) -o $(EXEC_NAME)

%.o: %.c $(HEADERFILES)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJFILES)

fclean: clean
	rm -f $(EXEC_NAME)

re: 
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean re
