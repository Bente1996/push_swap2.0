/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   sort_small_list.c                                       :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/05/22 17:40:42 by bede-kon            #+#    #+#           */
/*   Updated: 2026/05/22 17:41:59 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_small_list(t_node **A, t_node **B, int all)
{
	while (all)
	{
		if (all == 3)
		{
			sort_three(A);
			break ;
		}
		smallest_to_top(A);
		pb(A, B);
		all--;
	}
	while (*B)
		pa(A, B, 0);
}

void	smallest_to_top(t_node **A)
{
	int	mid_stack;
	int	smallest_pos;

	smallest_pos = find_smallest(*A);
	mid_stack = stack_size(*A) / 2;
	if (mid_stack < smallest_pos) // van onderaan
	{
		while (smallest_pos <= stack_size(*A))
		{
			rra(A, 0);
			smallest_pos++;
		}
	}
	else // vanaf boven
	{
		while (smallest_pos > 1)
		{
			ra(A, 0);
			smallest_pos--;
		}
	}
}

int	find_smallest(t_node *A)
{
	int		pos;
	int		smallest_pos;
	t_node	*smallest;

	pos = 1;
	smallest_pos = 1;
	smallest = A;
	while (A)
	{
		if (A->value < smallest->value)
		{
			smallest = A;
			smallest_pos = pos;
		}
		A = A->next;
		pos++;
	}
	return (smallest_pos);
}

void	sort_three(t_node **A)
{
	const int	one = (*A)->value;
	const int	two = (*A)->next->value;
	const int	three = (*A)->next->next->value;

	if (one > two && one > three) // 3 1 2 || 3 2 1
	{
		ra(A, 0);
		if (two > three)
			sa(A, 0);
	}
	else if (one > two && one < three) // 2 1 3
		sa(A, 0);
	else if (one < two && one > three) // 2 3 1
		rra(A, 0);
	else if (one < two && one < three) // 1 3 2
	{
		rra(A, 0);
		sa(A, 0);
	}
}
