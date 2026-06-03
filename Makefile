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
		top_to_quarter.c \
		quarter_to_half.c \
		sorting.c \
		organising.c \
		organising_utils.c \
		lowering.c \
		lowering_utils.c \
		grow_list.c \
		grow_list_utils.c \

VPATH = src/ \
		src/linked_list \
		src/operations \
		src/parsing \
		src/sort_big_list \
		src/sort_medium_list \
		src/sort_small_list

OBJDIR := bin/
OBJ := $(addprefix $(OBJDIR), $(SRC:.c=.o))

$(OBJDIR)%.o: %.c $(HEADER_FILES) | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

CFLAGS ?= -Wall -Wextra -Werror -I. -g 

all: $(NAME)

run: $(NAME)
	./$(NAME) 1 2 3 4

valgrind: $(NAME)
	valgrind ./$(NAME) 1 2 3 4

valgrind_full: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(NAME) 1 2 3 4

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

# %.o: %.c $(HEADER_FILES) 
# 	$(CC) $(CFLAGS) -c $< -o $@

%/ :
	@mkdir -p $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: 
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean re
