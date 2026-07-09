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

# include <stdbool.h>

typedef struct s_node
{
	int				value;
	int				index;
	int				n_index;
	struct s_node	*next;
}	t_node;

typedef struct s_text_node
{
	const char			*text;
	struct s_text_node	*next;
}	t_text;

typedef struct s_stats
{
	int				quarter;
	int				q;
	int				three_quarter;
	int				tq;
	int				h;
	int				swap;
	int				swap_rot;
	int				lower;
	int				bottom;
	struct s_node	*bottom_stack;
}	t_stats;

t_node	*make_list(int argc, char const *const *argv, int *i, t_node **head);
t_node	*append_node(t_node **head, int value, int index);
t_stats	init_stats(int half);
int		make_number(char const *argv, bool *valid);
int		convert(char const *argv, bool *valid);
bool	is_overflow(char const *argv, int value, int sign);
bool	is_number(char const *argv);
bool	is_duplicate(t_node *head, int value);
t_node	*sort_indices(t_node **list);
bool	already_sorted(t_node *stack);
bool	sorted(t_node *stack, int half, char a_or_b);

int		stack_size(t_node *stack);
void	print_list(t_node *list, char stack);
int		count_operations(char *operation);
int		free_list(t_node *head);

void	sort_all(t_node **a, int all);

void	sort_small_list(t_node **a, t_node **b, int all);
void	smallest_to_top(t_node **a);
int		find_smallest(t_node *a);
void	sort_three(t_node **a);

void	sort_medium_list(t_node **a, t_node **b, int size);
void	split_list(t_node **a, t_node **b, int half);
bool	little_organise(t_node **b, int half);

void	sort_highest_half(t_node **a, t_node **b, int half);
void	tq_to_all(t_stats *data, t_node **a, t_node **b);
void	half_to_tq(t_stats *data, t_node **a, t_node **b);

void	sorted_to_a(t_node **a, t_node **b, int half, int quarter);
void	sort_lowest_half(t_node **a, t_node **b, int half);
void	top_to_quarter(t_stats *data, t_node **a, t_node **b);
void	quarter_to_half(t_stats *data, t_node **a, t_node **b);

void	sort_big_list(t_node **a, t_node **b, int all, int half);
void	organise_a(t_node **a, t_node **b, int all, int size);
void	organise_b(t_node **a, t_node **b, int half, int size);
void	sort_a(t_node **a, t_node **b, int half, int size);
void	sort_b(t_node **a, t_node **b, int half, int size);
void	sort_forty_five(t_node **a, t_node **b, int highest, int size);
void	sort_low(t_node **a, t_node **b, int highest, int count);
void	sort_medium(t_node **a, t_node **b, int highest, int count);
void	sort_high(t_node **a, t_node **b, int highest, int count);
void	sort_rest(t_node **a, t_node **b, int highest);
void	groups_of_fifteen(t_node **a, t_node **b, int highest, int count);
void	sort_fifteen_a(t_node **a, t_node **b, int highest, int count);
void	sort_fifteen_b(t_node **a, t_node **b, int highest, int count);
void	sort_fifteen_c(t_node **a, t_node **b, int highest, int count);

void	sort_half(t_node **a, t_node **b, int half, int count);
int		is_group(int n_index, int lower, int bottom);
void	sort_unorganised(t_node **a, t_node **b, int half, int count);
void	grow_list(t_stats *data, t_node **a, t_node **b, int group);
void	sort_bottom_stack(t_stats *data, t_node **a, t_node **b, int group);
void	move_to_top(t_stats *data, t_node **a, t_node **b);
void	add_one(t_stats *data, t_node **a);
void	add_more(t_stats *data, t_node **a);
void	move_to_bottom(t_stats *data, t_node **a, t_node **b);
void	try_more(t_stats *data, t_node **a);
t_node	*find_bottom(t_node *stack);
t_node	*check_bottom(t_node *stack);
void	get_third(t_stats *data, t_node **a);
void	try_third(t_stats *data, t_node **a);
void	try_second(t_stats *data, t_node **a);
void	second_correct(t_stats *data, t_node **a);
void	two_in_order(t_stats *data, t_node **a);
void	add_from_bottom(t_stats *data, t_node **a);
void	two_correct(t_stats *data, t_node **a);
void	one_correct(t_stats *data, t_node **a);
bool	add_second(t_stats *data, t_node **a);

void	get_third_r(t_stats *data, t_node **b);
void	try_third_r(t_stats *data, t_node **b);
void	try_second_r(t_stats *data, t_node **b);
void	second_correct_r(t_stats *data, t_node **b);
void	two_in_order_r(t_stats *data, t_node **b);
void	add_from_bottom_r(t_stats *data, t_node **b);
void	two_correct_r(t_stats *data, t_node **b);
void	one_correct_r(t_stats *data, t_node **b);
bool	add_second_r(t_stats *data, t_node **b);
void	move_to_top_r(t_stats *data, t_node **a, t_node **b);
void	add_one_r(t_stats *data, t_node **b);
void	add_more_r(t_stats *data, t_node **b);
void	move_to_bottom_r(t_stats *data, t_node **a, t_node **b);
void	try_more_r(t_stats *data, t_node **b);

void	pb(t_node **a, t_node **b);
void	pa(t_node **a, t_node **b);
void	ra(t_node **a);
void	rb(t_node **b);
void	rr(t_node **a, t_node **b);
void	rrb(t_node **b);
void	rra(t_node **a);
void	sa(t_node **a);
void	sb(t_node **b);

void	append_text(t_text **head, const char *op);
t_text	*create_node(const char *text);
bool	check_rotate(t_text *before_last, t_text *last, const char *op);
bool	check_r_rotate(t_text *before_last, t_text *last, const char *op);
bool	check_swap(t_text *before_last, t_text *last, const char *op);
bool	check_push(t_text *before_last, t_text *last, const char *op);
int		strcmp(const char *s1, const char *s2);

#endif
