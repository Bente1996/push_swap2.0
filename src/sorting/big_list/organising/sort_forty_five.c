/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   sort_forty_five.c                                       :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/08 17:58:29 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/08 18:02:18 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_forty_five(t_node **a, t_node **b, int half, int size)
{
	int	count;

	count = size;
	while (count--)
	{
		if ((*b)->n_index > half - (size - 44))
			rb(b);
		else if ((*b)->n_index < half - (size - 30))
			pa(a, b);
		else
		{
			pa(a, b);
			ra(a);
		}
	}
	sort_low(a, b, half - (size - 90), 60);
	sort_medium(a, b, half - (size - 90), 25);
	sort_high(a, b, half - (size - 90), 25);
}

void	sort_low(t_node **a, t_node **b, int highest, int count)
{
	while (count > 30)
	{
		if ((*a)->n_index > highest - 76)
			ra(a);
		else
		{
			pb(a, b);
			if ((*b)->n_index > highest - 86)
				rb(b);
		}
		count--;
	}
	while (count--)
	{
		if (count >= 20)
		{
			rrb(b);
			if ((*b)->n_index > highest - 81)
				pa(a, b);
		}
		else if (count >= 15)
			pb(a, b);
		else
			rra(a);
	}
}

void	sort_medium(t_node **a, t_node **b, int highest, int count)
{
	while (count > 10)
	{
		if ((*a)->n_index < highest - 65)
		{
			pb(a, b);
			if ((*b)->n_index > highest - 71)
				rb(b);
		}
		else
			ra(a);
		count--;
	}
	while (count--)
	{
		if (count >= 5)
			rrb(b);
		else
		{
			rra(a);
			pb(a, b);
		}
	}
}

void	sort_high(t_node **a, t_node **b, int highest, int count)
{
	while (count > 10)
	{
		rra(a);
		if ((*a)->n_index < highest - 50)
		{
			pb(a, b);
			if ((*b)->n_index > highest - 56)
				rb(b);
		}
		count--;
	}
	while (count--)
	{
		if (count >= 5)
			rrb(b);
		else
			pb(a, b);
	}
}
