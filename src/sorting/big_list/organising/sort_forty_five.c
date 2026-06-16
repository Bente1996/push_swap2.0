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
		if ((*b)->n_index > half - (size - 44)) // (115-250)
			rb(b);
		else if ((*b)->n_index < half - (size - 30)) // (99-70)
			pa(a, b);
		else                                             // (100-114)
		{
			pa(a,b);
			ra(a);
		}
	}
	sort_low(a, b, half - (size - 90), 60); 
	sort_medium(a, b, half - (size - 90), 25); 
	sort_high(a, b, half - (size - 90), 25);
}

void	sort_low(t_node **a, t_node **b, int highest, int count)
{
	while (count > 30) // 30
	{
		if ((*a)->n_index > highest - 76) // -61 tot -75 onderaan A
			ra(a);
		else                                       // -76 tot -90 bovenaan B
		{
			pb(a, b);
			if ((*b)->n_index > highest - 86) // -76 tot -85 naar beneden, -86 tot -90 al goed!
				rb(b);
		}
		count--;
	}
	while (count--)
	{
		if (count >= 20) // -81 tot -85 op goeie plek
		{
			rrb(b);
			if ((*b)->n_index > highest - 81) // -76 tot -80 naar A
				pa(a, b);
		}
		else if (count >= 15) // -76 tot -80
			pb(a, b);
		else                  // alles naar boven
			rra(a);
	}
}

void	sort_medium(t_node **a, t_node **b, int highest, int count)
{
	while (count > 10) // -61 tot -75 op goeie plek zetten
	{
		if ((*a)->n_index < highest - 65) // -66 tot -75 naar B
		{
			pb(a, b);
			if ((*b)->n_index > highest - 71) // -66 tot -70 onderaan B, -71 tot -75 op goeie plek
				rb(b);
		}
		else // -61 tot -65 onderaan A
		     ra(a);
		count--;
	}
	while(count--)
	{
		if (count >= 5)  // -66 tot -70
			rrb(b);
		else              // -61 tot -65
		{
			rra(a);
			pb(a, b);
		}
	}
}

void	sort_high(t_node **a, t_node **b, int highest, int count)
{
	while (count > 10) // -46 tot -60 op goeie plek zetten
	{
		rra(a); // alles naar boven
		if ((*a)->n_index < highest - 50) // -51 tot -60 op goeie plek zetten
		{
			pb(a, b); // -56 tot -60 staat goed
			if ((*b)->n_index > highest - 56) // -51 tot -55 naar beneden
				rb(b);
		}
		count--;
	}
	while (count--)
	{
		if (count >= 5) // -51 tot -55
			rrb(b);
		else            // -46 tot -50
			pb(a, b);
	}
}
