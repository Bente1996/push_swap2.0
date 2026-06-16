NAME := push_swap
HEADER_FILES := push_swap.h
SRC := main.c \
		list_utils.c \
		nodes.c \
		utils.c \
		parsing.c \
		parsing_utils.c \
		pa.c \
		pb.c \
		sa.c \
		sb.c \
		ra.c \
		rb.c \
		rra.c \
		rrb.c \
		sort_small_list.c \
		sort_medium_list.c \
		sort_highest_half.c \
		half_to_tq.c \
		tq_to_all.c \
		sort_lowest_half.c \
		top_to_quarter.c \
		quarter_to_half.c \
		sorting.c \
		sort_big_list.c \
		organise_a.c \
		organise_b.c \
		sort_forty_five.c \
		sort_rest.c \
		move_to_top.c \
		try_more.c \
		second_correct.c \
		get_third.c \
		sort_half.c \
		sort_unorganised.c \
		move_to_bottom.c \
		move_to_top_r.c \
		try_more_r.c \
		second_correct_r.c \
		get_third_r.c

VPATH = src/ \
		src/linked_list \
		src/operations \
		src/sorting \
		src/sorting/small_list\
		src/sorting/medium_list \
		src/sorting/big_list \
		src/sorting/big_list/organising \
		src/sorting/big_list/sorting \
		src/sorting/big_list/sorting/move_to_top \
		src/sorting/big_list/sorting/move_to_top_r

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
