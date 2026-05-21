NAME := push_swap
HEADER_FILES := push_swap.h
SRC := main.c \
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


OBJ := $(addprefix $(OBJDIR), $(SRC:.c=.o))

$(OBJDIR)%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -co $@ $<

CFLAGS ?= -Wall -Wextra -Werror -g 

all: $(NAME)

run: $(NAME)
	./$(NAME) 1 2 3 4

valgrind: $(NAME)
	valgrind ./$(NAME) 1 2 3 4

valgrind full: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(NAME) 1 2 3 4

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: 
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean re
