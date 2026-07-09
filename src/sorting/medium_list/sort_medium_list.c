/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   sort_medium_list.c                                      :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/05/25 16:48:21 by bede-kon            #+#    #+#           */
/*   Updated: 2026/05/25 17:12:45 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// all % 2 needs to be added to half because of the fractional part in integer
// division being truncated to 0
void	sort_medium_list(t_node **a, t_node **b, int all)
{
	int		half;

	half = all / 2;
	split_list(a, b, half);
	sort_highest_half(a, b, half);
	sorted_to_a(a, b, half + (all % 2), half / 2);
	sort_lowest_half(a, b, half);
}

void	split_list(t_node **a, t_node **b, int half)
{
	int		h;
	int		count;

	h = half;
	count = 0;
	while (h)
	{
		if ((*a)->n_index < half)
		{
			pb(a, b);
			if ((*b)->n_index < 3 || (*b)->n_index > half - 4)
			{
				rb(b);
				count++;
			}
			h--;
		}
		else
			ra(a);
	}
	while (count--)
		rrb(b);
}

void	sorted_to_a(t_node **a, t_node **b, int half, int quarter)
{
	quarter++;
	while (half > quarter)
	{
		rrb(b);
		pa(a, b);
		half--;
	}
	while (half--)
		pa(a, b);
}
