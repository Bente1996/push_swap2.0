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

#include <stdbool.h>

typedef struct s_node
{
	int		value;
	int		index;
	int		sorted_index;
	struct s_node	*next;
}	t_node;

typedef struct s_stats
{
	struct s_node	*stack_a;
	struct s_node	*stack_b;
	int	tq;
	int	h;
	int	swap;
	int	swap_rot;
	int	lower;
	int	bottom;
	struct s_node	*bottom_stack;
}	t_stats;

t_node	*append_node(t_node **head, int value, int index);
t_node	*make_list(int argc, char **argv, int *i);
int	make_number(char *argv, int *valid);
int	convert(char *argv, int *valid);
bool	is_overflow(char *argv, int value, int sign);
bool	is_number(char *argv);
bool	is_duplicate(t_node *head, int value);
int	free_list(t_node *head);
t_node	*sort_indices(t_node **list);
int	random_split(t_node **stack_a, t_node **stack_b, int size);
bool	in_group(t_node *stack_b, int *arr, int highest);
int	move_highest(int *arr, int highest);
void	check_shift(int *arr, int sum);
void	shift_group(int *arr, int n);
void	intentional_split(t_node **stack_a, t_node **stack_b, int half);
void	big_list(t_node **stack_a, t_node **stack_b, int half);
void	grow_list(t_node **stack_a, t_node **stack_b, int half, int count);
bool	sorted(t_node *stack, int half, char A_or_B);
bool	already_sorted(t_node *stack);
void	pb(t_node **stack_a, t_node **stack_b);
void	pa(t_node **stack_a, t_node **stack_b);
void	ra(t_node **stack_a);
void	rb(t_node **stack_b);
void	rr(t_node **stack_a, t_node **stack_b);
void	rrb(t_node **stack_b);
void	rra(t_node **stack_a);
void	sa(t_node **stack_a);
void	sb(t_node **stack_b);
bool	one_element(t_node **stack_a, t_node **stack_b, int half);
int	stack_size(t_node *stack);
void	print_list(t_node *list, char stack); // naar ft_printf doen
int	count_operations(char *operation);
t_node *find_bottom(t_node *stack);
t_node	*check_bottom(t_node *stack);
void	sorted_to_A(t_node **A, t_node **B, int half, int quarter);
int	find_case(int sorted_index, int lower, int bottom);
t_stats	*alloc_stats(t_node **stack_a, t_node **stack_b, int half);
void	case_one(t_stats *data);
void	case_two(t_stats *data);
void	handle_bottom(t_stats *data);
void	more_bottom(t_stats *data);
void	get_third(t_stats *data);
void	try_three(t_stats *data);
void	try_two(t_stats *data);
void	get_second(t_stats *data);
void	check_third(t_stats *data);
void	funk(t_stats *data);
void	fonk(t_stats *data);
bool	add_second(t_stats *data);
void	swap(t_stats *data);
void	upper_quarter(t_stats *data);
void	lower_quarter(t_stats *data);
void	swop(t_stats *data);
void	swap_two(t_stats *data);
void	more_swap(t_stats *data);
void	group_sort(t_node **stack_a, t_node **stack_b, int highest, int group_size);
void	sort_all(t_node **stack_a, t_node **stack_b, int size);
void	sort_rest(t_node **stack_a, t_node **stack_b, int highest);
void	sort_quarter(t_node **stack_a, t_node **stack_b, int highest, int size);
void	sort_low(t_node **stack_a, t_node **stack_b, int highest);
void	sort_medium(t_node **stack_a, t_node **stack_b, int highest);
void	sort_high(t_node **stack_a, t_node **stack_b, int highest);
void	split_list(t_node **stack_a, t_node **stack_b, int half);
void	split_B(t_node **stack_b, int highest);
void	split_A(t_node **stack_a, t_node **stack_b, int highest);
void	sort_B(t_node **stack_a, t_node **stack_b, int half);
void	organise_A(t_node **stack_a, t_node **stack_b, int half);

#endif
