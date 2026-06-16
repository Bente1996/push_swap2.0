/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   organising.c                                            :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/05 21:57:08 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/05 23:21:19 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	organise_b(t_node **a, t_node **b, int half, int size)
{
	int	h;

	h = half;
	while (h)
	{
		if ((*a)->n_index < half)
		{
			pb(a, b);
			h--;
			if (((*b)->n_index < half - size))
					rb(b);
		}
		else
			ra(a);
	}
	sort_b(a, b, half, size);
}

void	sort_b(t_node **a, t_node **b, int half, int size)
{
	int count;

	count = half - size + 45;
	sort_forty_five(a, b, half, size); // 0-135 beneden
	if (size >= 135)
	{
		while (count--)
			rb(b);
		sort_forty_five(a, b, half, size - 45); // 0-90 beneden
	}
	if (size == 180)
	{
		count = 90; // van 90 naar 89 gedaan voor 499
		while (count--)
			rrb(b);
		sort_forty_five(a, b, half, 90); // 45 beneden
	}
	if (size >= 90)
		sort_rest(a, b, half); // sorteert laatste
}
