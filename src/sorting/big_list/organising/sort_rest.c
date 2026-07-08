/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   sort_fifteen.c                                          :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/08 17:55:47 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/08 18:02:15 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_rest(t_node **a, t_node **b, int highest)
{
	groups_of_fifteen(a, b, highest, 45);
	sort_fifteen_a(a, b, highest, 30);
	sort_fifteen_b(a, b, highest, 25);
	sort_fifteen_c(a, b, highest, 25);
}

void	groups_of_fifteen(t_node **a, t_node **b, int highest, int count)
{
	while (count--)
	{
		rrb(b);
		if ((*b)->n_index > highest - 16)
		{
			pa(a, b);
			ra(a);
		}
		else if ((*b)->n_index < highest - 15 && (*b)->n_index > highest - 31)
			pa(a, b);
	}
}

void	sort_fifteen_a(t_node **a, t_node **b, int highest, int count)
{
	while (count > 15)
	{
		if ((*b)->n_index >= highest - 35)
		{
			pa(a, b);
			ra(a);
		}
		else if ((*b)->n_index >= highest - 40)
			rb(b);
		else
			pa(a, b);
		count--;
	}
	while (count--)
	{
		if (count >= 10)
			pb(a, b);
		else if (count >= 5)
			rrb(b);
		else
		{
			rra(a);
			pb(a, b);
		}
	}
}

void	sort_fifteen_b(t_node **a, t_node **b, int highest, int count)
{
	while (count > 10)
	{
		if ((*a)->n_index >= highest - 20)
			ra(a);
		else if ((*a)->n_index >= highest - 25)
		{
			pb(a, b);
			rb(b);
		}
		else
			pb(a, b);
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

void	sort_fifteen_c(t_node **a, t_node **b, int highest, int count)
{
	while (count > 10)
	{
		rra(a);
		if ((*a)->n_index < highest - 5)
		{
			pb(a, b);
			if ((*b)->n_index >= highest - 10)
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
