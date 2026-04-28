EXEC_NAME := push_swap
HEADERFILES := push_swap.h
SRCFILES := main.c \
	    parsing.c \
	    utils.c \
	    nodes.c \
		sorting.c \
		operations.c \
		random_split.c \
		big_list.c \
		final_list.c \
		method_two.c

OBJFILES := $(SRCFILES:.c=.o)
CFLAGS ?= -Wall -Wextra -Werror -g 

all: $(EXEC_NAME)

run: $(EXEC_NAME)
	./$(EXEC_NAME) 1 2 3 4

valgrind: $(EXEC_NAME)
	valgrind ./$(EXEC_NAME) 1 2 3 4

valgrind full: $(EXEC_NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(EXEC_NAME) 1 2 3 4

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
