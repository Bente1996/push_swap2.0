#include "push_swap.h"

void	sort_quarter(t_node **stack_a, t_node **stack_b, int half, int size)
{
	int	count;

	count = size;
	while (count)
	{
		if ((*stack_b)->n_index > half - (size - 44)) // (115-250)
			rb(stack_b, 0);
		else if ((*stack_b)->n_index < half - (size - 30)) // (99-70)
			pa(stack_a, stack_b, 0);
		else                                             // (100-114)
		{
			pa(stack_a,stack_b, 0);
			ra(stack_a, 0);
		}
		count--;
	}
	sort_low(stack_a, stack_b, half - (size - 90)); 
	sort_medium(stack_a, stack_b, half - (size - 90)); 
	sort_high(stack_a, stack_b, half - (size - 90));
}

void	sort_low(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 30; // eert 60
	while (count--) // 30
	{
		if ((*stack_a)->n_index > highest - 76) // -61 tot -75 onderaan A
			ra(stack_a, 0);
		else                                       // -76 tot -90 bovenaan B
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->n_index > highest - 86) // -76 tot -85 naar beneden, -86 tot -90 al goed!
				rb(stack_b, 0);
		}
	}
	count = 10;
	while (count--) // -81 tot -85 op goeie plek zetten
	{
		rrb(stack_b);
		if ((*stack_b)->n_index > highest - 81) // -76 tot -80 naar A
			pa(stack_a, stack_b, 0);
	}
	count = 5;
	while (count--) // -76 tot -80 op goeie plek zetten
		pb(stack_a, stack_b);
	count = 15;
	while (count--)
		rra(stack_a, 0); // alles naaar boven
}

void	sort_medium(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 15;
	while (count--) // -61 tot -75 op goeie plek zetten
	{
		if ((*stack_a)->n_index < highest - 65) // -66 tot -75 naar B
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->n_index > highest - 71) // -66 tot -70 onderaan B, -71 tot -75 op goeie plek
				rb(stack_b, 0);
		}
		else // -61 tot -65 onderaan A
		     ra(stack_a, 0);
	}
	count = 5;
	while (count--)
		rrb(stack_b); // -66 tot -70 op goeie plek zetten
	count = 5;
	while (count--)
	{
		rra(stack_a, 0);
		pb(stack_a, stack_b); // -61 tot -65 op goeie plek zetten
	}
}

void	sort_high(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 15;
	while (count--) // -46 tot -60 op goeie plek zetten
	{
		rra(stack_a, 0); // alles naar boven
		if ((*stack_a)->n_index < highest - 50) // -51 tot -60 op goeie plek zetten
		{
			pb(stack_a, stack_b); // -56 tot -60 staat goed
			if ((*stack_b)->n_index > highest - 56) // -51 tot -55 naar beneden
				rb(stack_b, 0);
		}
	}
	count = 5;
	while (count--) // -51 tot -55 op goeie plek zetten
		rrb(stack_b);
	count = 5;
	while (count--) // -46 tot -50 op goeie plek zetten
		pb(stack_a, stack_b);
}

#include <stdio.h>

void	sort_rest(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 45;
	while (count--) // 45
	{
		rrb(stack_b); // -31 tot -45 blijft in B
		if ((*stack_b)->n_index > highest - 16) // begin: -1 tot -15
		{
			pa(stack_a, stack_b, 0);
			ra(stack_a, 0);
		}
		else if ((*stack_b)->n_index < highest - 15 && (*stack_b)->n_index > highest - 31) // -16 tot -30
			pa(stack_a, stack_b, 0);
		else if (highest == 50)
			rb(stack_b, 0); // voor 100!!!
		else if (highest == 95)
			rb(stack_b, 0);
	}
	
	count = 15;
	while (count--) // 15
	{
		if ((*stack_b)->n_index >= highest - 35) // -31 tot -35
		{
			pa(stack_a, stack_b, 0);
			ra(stack_a, 0);
		}
		else if ((*stack_b)->n_index >=highest - 40) // -36 tot -40
			rb(stack_b, 0);
		else // -41 tot -45
		     pa(stack_a, stack_b, 0);
	}
	count = 5;
	while (count--) // 5
		pb(stack_a, stack_b); // -41 tot -45 goed
	count = 5;
	while (count--) //5
		rrb(stack_b); // -36 tot -40 goed
	count = 5;
	while (count--) // 5
	{
		rra(stack_a, 0);
		pb(stack_a, stack_b); // -30 tot -35 goed
	}
	count = 15;
	while (count--) // 15
	{
		if ((*stack_a)->n_index >= highest - 20)  // -16 tot -20
			ra(stack_a, 0);
		else if ((*stack_a)->n_index >= highest - 25) // -21 tot -25
		{
			pb(stack_a, stack_b);
			rb(stack_b, 0);
		}
		else // -26 tot -30
		     pb(stack_a, stack_b); // staat nu al goed
	}
	count = 5;
	while (count--) // 5
		rrb(stack_b); // -21 tot -25 goed
	count = 5;
	while (count--) // 5
	{
		rra(stack_a, 0);
		pb(stack_a, stack_b); // -16 tot -20 goed
	}
	count = 15;
	while (count--) // 15
	{
		rra(stack_a, 0); // -1 tot -5
		if ((*stack_a)->n_index < highest - 5) // -11 tot -15 gelijk goed
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->n_index >= highest - 10) // -6 tot -10
				rb(stack_b, 0);
		}
	}
	count = 5;
	while (count--) // 5
		rrb(stack_b); // -6 tot -10 goed
	count = 5;
	while (count--) // 5
		pb(stack_a, stack_b); // -1 tot -5 goed
}
