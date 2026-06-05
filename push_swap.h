
/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   push_swap.h                                             :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/12 20:16:01 by bede-kon            #+#    #+#           */
/*   Updated: 2026/03/12 20:16:04 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#define UNEVEN all % 2

#include <stdbool.h>

typedef struct s_node
{
	int		value;
	int		index;
	int		n_index;
	struct s_node	*next;
}	t_node;

typedef struct s_stats
{
	int	top;
	int	quarter;
	int	q;
	int	three_quarter;
	int	tq;
	int	h;
	int	swap;
	int	swap_rot;
	int	lower;
	int	bottom;
	struct s_node	*bottom_stack;
}	t_stats;

t_node	*make_list(int argc, char **argv, int *i);
t_node	*append_node(t_node **head, int value, int index);
t_stats	*alloc_stats(t_node **stack_a, t_node **stack_b, int half);
int		make_number(char *argv, int *valid);
int		convert(char *argv, int *valid);
bool	is_overflow(char *argv, int value, int sign);
bool	is_number(char *argv);
bool	is_duplicate(t_node *head, int value);
t_node	*sort_indices(t_node **list);
bool	already_sorted(t_node *stack);
bool	sorted(t_node *stack, int half, char A_or_B);

int		stack_size(t_node *stack);
void	print_list(t_node *list, char stack); // naar ft_printf doen
int		count_operations(char *operation);
int		free_list(t_node *head);


void	sort_all(t_node **stack_a, t_node **stack_b, int all);

void	sort_small_list(t_node **A, t_node **B, int all);
void	smallest_to_top(t_node **A);
int		find_smallest(t_node *A);
void	sort_three(t_node **A);



void	sort_medium_list(t_node **A, t_node **B, int size);
void	split_list(t_node **A, t_node **B, int half);
bool	little_organise(t_node **B, int half);

void	sort_highest_half(t_node **A, t_node **B, int half);
void	tq_to_all(t_stats *data, t_node **A, t_node **B); // check volgorde
void	half_to_tq(t_stats *data, t_node **A, t_node **B); // check volgorde (naam)

void	sorted_to_A(t_node **A, t_node **B, int half, int quarter);
void	sort_lowest_half(t_node **A, t_node **B, int half);
void	top_to_quarter(t_stats *data, t_node **A, t_node **B);
void	quarter_to_half(t_stats *data, t_node **A, t_node **B);



void	sort_big_list(t_node **stack_a, t_node **stack_b, int all, int half); // ook
																			  // dubbele
																			  // (static
																			  // functions
																			  // maken)
void	organise_A(t_node **stack_a, t_node **stack_b, int all, int size);
void	organise_B(t_node **stack_a, t_node **stack_b, int half, int size);
void	sort_A(t_node **stack_a, t_node **stack_b, int half, int size);
void	sort_B(t_node **stack_a, t_node **stack_b, int half, int size);
void	grow_list(t_node **A, t_node **B, int half, int count);
int	find_case(int sorted_index, int lower, int bottom);
void	add(t_stats *data, t_node **A, t_node **B);
void	add_and_lower(t_stats *data, t_node **A, t_node **B);
void	sort_forty_five(t_node **stack_a, t_node **stack_b, int highest, int size);
void	sort_low(t_node **stack_a, t_node **stack_b, int highest, int count);
void	sort_medium(t_node **stack_a, t_node **stack_b, int highest, int count);
void	sort_high(t_node **stack_a, t_node **stack_b, int highest, int count);
void	sort_rest(t_node **stack_a, t_node **stack_b, int highest);
void	handle_bottom(t_stats *data, t_node **A);
void	more_bottom(t_stats *data, t_node **A);
t_node *find_bottom(t_node *stack);
t_node	*check_bottom(t_node *stack);
void	get_third(t_stats *data, t_node **A);
void	try_three(t_stats *data, t_node **A);
void	try_two(t_stats *data, t_node **A);
void	get_second(t_stats *data, t_node **A);
void	check_third(t_stats *data, t_node **A);
void	funk(t_stats *data, t_node **A);
void	fonk(t_stats *data, t_node **A);
bool	add_second(t_stats *data, t_node **A);



void	pb(t_node **stack_a, t_node **stack_b);
void	pa(t_node **stack_a, t_node **stack_b, int top);
void	ra(t_node **stack_a, int top);
void	rb(t_node **stack_b, int top);
void	rr(t_node **stack_a, t_node **stack_b);
void	rrb(t_node **stack_b);
void	rra(t_node **stack_a, int top);
void	sa(t_node **stack_a, int top);
void	sb(t_node **stack_b);

#endif
