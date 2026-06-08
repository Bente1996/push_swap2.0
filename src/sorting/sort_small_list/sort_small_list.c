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

void	sort_small_list(t_node **a, t_node **b, int all)
{
	while (all)
	{
		if (all == 3)
		{
			sort_three(a);
			break ;
		}
		smallest_to_top(a);
		pb(a, b);
		all--;
	}
	while (*b)
		pa(a, b, 0);
}

void	smallest_to_top(t_node **a)
{
	int	mid_stack;
	int	smallest_pos;

	smallest_pos = find_smallest(*a);
	mid_stack = stack_size(*a) / 2;
	if (mid_stack < smallest_pos) // van onderaan
	{
		while (smallest_pos <= stack_size(*a))
		{
			rra(a, 0);
			smallest_pos++;
		}
	}
	else // vanaf boven
	{
		while (smallest_pos > 1)
		{
			ra(a, 0);
			smallest_pos--;
		}
	}
}

int	find_smallest(t_node *b)
{
	int		pos;
	int		smallest_pos;
	t_node	*smallest;

	pos = 1;
	smallest_pos = 1;
	smallest = b;
	while (b)
	{
		if (b->value < smallest->value)
		{
			smallest = b;
			smallest_pos = pos;
		}
		b = b->next;
		pos++;
	}
	return (smallest_pos);
}

void	sort_three(t_node **a)
{
	const int	one = (*a)->value;
	const int	two = (*a)->next->value;
	const int	three = (*a)->next->next->value;

	if (one > two && one > three) // 3 1 2 || 3 2 1
	{
		ra(a, 0);
		if (two > three)
			sa(a, 0);
	}
	else if (one > two && one < three) // 2 1 3
		sa(a, 0);
	else if (one < two && one > three) // 2 3 1
		rra(a, 0);
	else if (one < two && one < three) // 1 3 2
	{
		rra(a, 0);
		sa(a, 0);
	}
}
