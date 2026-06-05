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
					rb(b, 0);
		}
		else
			ra(a, 0);
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
			rb(b, 0);
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

void	organise_a(t_node **a, t_node **b, int all, int highest)
{
	int	size;
	int	half;

	half = all / 2;
	size = highest - half;
	if (all % 2)
		half++;
	while (half--)
	{
		if ((*a)->n_index < highest)
			pb(a, b);
		else
			ra(a, 0);
	}
	sort_a(a, b, highest, size);
}

void	sort_a(t_node **a, t_node **b, int highest, int size)
{
	int count;

	count = 90;
	sort_forty_five(a, b, highest, size); // 0-135 beneden
	if (size >= 135)
	{
		if (size == 180)
			count += 45;
		while (count--) // 135
			rrb(b);
		sort_forty_five(a, b, highest, size - 45); // 0-90 beneden
	}
	if (size == 180)
	{
		count = 90;
		while (count--) // 90
			rrb(b);
		sort_forty_five(a, b, highest, 90); // 45 beneden
	}
	if (size >= 90)
		sort_rest(a, b, highest); // sorteert laatste 45
}
