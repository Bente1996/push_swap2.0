EXEC_NAME := push_swap
HEADERFILES := push_swap.h
SRCFILES := main.c \
	    list_utils.c \
	    parsing.c \
	    parsing_utils.c \
		sorting.c \
		sorting_utils.c \
		p_and_s.c \
		r_and_rr.c \
		organising_small.c \
		organising_utils.c \
		utils.c \
		nodes.c \
		swapping.c \
		big_list.c \
		grow_list.c \
		grow_list_utils.c \
		hundred.c \
		lowering.c \
		lowering_utils.c


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
