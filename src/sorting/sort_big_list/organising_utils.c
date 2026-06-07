#include "push_swap.h"

void	sort_forty_five(t_node **a, t_node **b, int half, int size)
{
	int	count;

	count = size;
	while (count--)
	{
		if ((*b)->n_index > half - (size - 44)) // (115-250)
			rb(b, 0);
		else if ((*b)->n_index < half - (size - 30)) // (99-70)
			pa(a, b, 0);
		else                                             // (100-114)
		{
			pa(a,b, 0);
			ra(a, 0);
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
			ra(a, 0);
		else                                       // -76 tot -90 bovenaan B
		{
			pb(a, b);
			if ((*b)->n_index > highest - 86) // -76 tot -85 naar beneden, -86 tot -90 al goed!
				rb(b, 0);
		}
		count--;
	}
	while (count--)
	{
		if (count >= 20) // -81 tot -85 op goeie plek
		{
			rrb(b);
			if ((*b)->n_index > highest - 81) // -76 tot -80 naar A
				pa(a, b, 0);
		}
		else if (count >= 15) // -76 tot -80
			pb(a, b);
		else                  // alles naar boven
			rra(a, 0);
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
				rb(b, 0);
		}
		else // -61 tot -65 onderaan A
		     ra(a, 0);
		count--;
	}
	while(count--)
	{
		if (count >= 5)  // -66 tot -70
			rrb(b);
		else              // -61 tot -65
		{
			rra(a, 0);
			pb(a, b);
		}
	}
}

void	sort_high(t_node **a, t_node **b, int highest, int count)
{
	while (count > 10) // -46 tot -60 op goeie plek zetten
	{
		rra(a, 0); // alles naar boven
		if ((*a)->n_index < highest - 50) // -51 tot -60 op goeie plek zetten
		{
			pb(a, b); // -56 tot -60 staat goed
			if ((*b)->n_index > highest - 56) // -51 tot -55 naar beneden
				rb(b, 0);
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

void	groups_of_fifteen(t_node **a, t_node **b, int highest, int count)
{
	while (count--) // 45
	{
		rrb(b); // -31 tot -45 blijft in B
		if ((*b)->n_index > highest - 16) // begin: -1 tot -15
		{
			pa(a, b, 0);
			ra(a, 0);
		}
		else if ((*b)->n_index < highest - 15 && (*b)->n_index > highest - 31) // -16 tot -30
			pa(a, b, 0);
	}
}

void	sort_fifteen_A(t_node **a, t_node **b, int highest, int count)
{
	while (count > 15) // 15
	{
		if ((*b)->n_index >= highest - 35) // -31 tot -35
		{
			pa(a, b, 0);
			ra(a, 0);
		}
		else if ((*b)->n_index >=highest - 40) // -36 tot -40
			rb(b, 0);
		else // -41 tot -45
		     pa(a, b, 0);
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
			rra(a, 0);
			pb(a, b);
		}
	}
}

void	sort_fifteen_B(t_node **a, t_node **b, int highest, int count)
{
	while (count > 10) // 15
	{
		if ((*a)->n_index >= highest - 20)  // -16 tot -20
			ra(a, 0);
		else if ((*a)->n_index >= highest - 25) // -21 tot -25
		{
			pb(a, b);
			rb(b, 0);
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
			rra(a, 0);
			pb(a, b);
		}
	}
}

void	sort_fifteen_C(t_node **a, t_node **b, int highest, int count)
{
	while (count > 10) // 15
	{
		rra(a, 0); // -1 tot -5
		if ((*a)->n_index < highest - 5) // -11 tot -15 gelijk goed
		{
			pb(a, b);
			if ((*b)->n_index >= highest - 10) // -6 tot -10
				rb(b, 0);
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

void	sort_rest(t_node **a, t_node **b, int highest) // highest in struct doen (misschien)
{
	groups_of_fifteen(a, b, highest, 45);
	sort_fifteen_A(a, b, highest, 30);
	sort_fifteen_B(a, b, highest, 25);
	sort_fifteen_C(a, b, highest, 25);
}
