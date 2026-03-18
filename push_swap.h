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
	struct s_node *next;
}	t_node;

t_node	*append_node(t_node **head, int value, int index);
t_node	*make_list(int argc, char **argv, int *i);
int	make_number(char *argv, int *valid);
int	convert(char *argv, int *valid);
bool	is_overflow(char *argv, int value, int sign);
bool	is_number(char *argv);
bool	is_duplicate(t_node *head, int value);
void	free_list(t_node *head);
t_node	*sort_indices(t_node **list);
int	random_split(t_node **stack_a, t_node **stack_b, int size);
void	intentional_split(t_node **stack_a, t_node **stack_b, int half);
void	big_list(t_node **stack_a, t_node **stack_b, int half);
bool	sorted(t_node *stack, int half, char A_or_B);
void	pb(t_node **stack_a, t_node **stack_b);
void	pa(t_node **stack_a, t_node **stack_b);
void	ra(t_node **stack_a);
void	rb(t_node **stack_b);
void	rr(t_node **stack_a, t_node **stack_b);
void	sa(t_node **stack_a);
void	sb(t_node **stack_b);
bool	one_element(t_node **stack_a, t_node **stack_b, int half);
int	stack_size(t_node *stack);
void	print_list(t_node *list, char stack); // naar ft_printf doen
int	count_operations(char *operation);

#endif
