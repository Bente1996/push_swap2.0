NAME := push_swap
HEADER_FILES := push_swap.h
SRC := main.c \
		list_utils.c \
		nodes.c \
		utils.c \
		parsing.c \
		parsing_utils.c \
		p_and_s.c \
		r_and_rr.c \
		sort_small_list.c \
		sort_medium_list.c \
		sort_highest_half.c \
		half_to_tq.c \
		tq_to_all.c \
		sort_lowest_half.c \
		sorting.c \
		organising.c \
		organising_utils.c \
		lowering.c \
		lowering_utils.c \
		grow_list.c \
		grow_list_utils.c \

VPATH = src:..

OBJ := $(SRC:.c=.o)
#OBJ := $(addprefix $(OBJDIR), $(SRC:.c=.o))

#$(OBJDIR)%.o: %.c $(HEADER_FILES)
#	$(CC) $(CFLAGS) -co $@ $<

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
