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

void	sort_rest(t_node **a, t_node **b, int highest) // highest in struct doen (misschien)
{
	groups_of_fifteen(a, b, highest, 45);
	sort_fifteen_A(a, b, highest, 30);
	sort_fifteen_B(a, b, highest, 25);
	sort_fifteen_C(a, b, highest, 25);
}

void	groups_of_fifteen(t_node **a, t_node **b, int highest, int count)
{
	while (count--) // 45
	{
		rrb(b); // -31 tot -45 blijft in B
		if ((*b)->n_index > highest - 16) // begin: -1 tot -15
		{
			pa(a, b);
			ra(a);
		}
		else if ((*b)->n_index < highest - 15 && (*b)->n_index > highest - 31) // -16 tot -30
			pa(a, b);
	}
}

void	sort_fifteen_A(t_node **a, t_node **b, int highest, int count)
{
	while (count > 15) // 15
	{
		if ((*b)->n_index >= highest - 35) // -31 tot -35
		{
			pa(a, b);
			ra(a);
		}
		else if ((*b)->n_index >=highest - 40) // -36 tot -40
			rb(b);
		else // -41 tot -45
		     pa(a, b);
		count--;
	}
	while (count--)
	{
		if (count >= 10) // -41 tot -45
			pb(a, b);
		else if (count >= 5) // -36 tot -40
			rrb(b);
		else             // -30 tot -35
		{
			rra(a);
			pb(a, b);
		}
	}
}

void	sort_fifteen_B(t_node **a, t_node **b, int highest, int count)
{
	while (count > 10) // 15
	{
		if ((*a)->n_index >= highest - 20)  // -16 tot -20
			ra(a);
		else if ((*a)->n_index >= highest - 25) // -21 tot -25
		{
			pb(a, b);
			rb(b);
		}
		else // -26 tot -30
		     pb(a, b); // staat nu al goed
		count--;
	}
	while (count--)
	{
		if (count >= 5) // -21 tot -25 goed
			rrb(b);
		else            // -16 tot -20 goed
		{
			rra(a);
			pb(a, b);
		}
	}
}

void	sort_fifteen_C(t_node **a, t_node **b, int highest, int count)
{
	while (count > 10) // 15
	{
		rra(a); // -1 tot -5
		if ((*a)->n_index < highest - 5) // -11 tot -15 gelijk goed
		{
			pb(a, b);
			if ((*b)->n_index >= highest - 10) // -6 tot -10
				rb(b);
		}
		count--;
	}
	while (count--)
	{
		if (count >= 5) // -6 tot -10
			rrb(b);
		else            // -1 tot -5
			pb(a, b);
	}
}
