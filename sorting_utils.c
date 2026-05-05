#include "push_swap.h"

void	sort_high(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 30; // eert 60
	while (count--) // 30
	{
		if ((*stack_a)->sorted_index > highest - 76) // -61 tot -75 onderaan A
			ra(stack_a);
		else                                       // -76 tot -90 bovenaan B
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->sorted_index > highest - 86) // -76 tot -85 naar beneden, -86 tot -90 al goed!
				rb(stack_b);
		}
	}
	count = 10;
	while (count--) // -81 tot -85 op goeie plek zetten
	{
		rrb(stack_b);
		if ((*stack_b)->sorted_index > highest - 81) // -76 tot -80 naar A
			pa(stack_a, stack_b);
	}
	count = 5;
	while (count--) // -76 tot -80 op goeie plek zetten
		pb(stack_a, stack_b);
	count = 15;
	while (count--)
		rra(stack_a); // alles naaar boven
}

void	sort_medium(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 15;
	while (count--) // -61 tot -75 op goeie plek zetten
	{
		if ((*stack_a)->sorted_index < highest - 65) // -66 tot -75 naar B
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->sorted_index > highest - 71) // -66 tot -70 onderaan B, -71 tot -75 op goeie plek
				rb(stack_b);
		}
		else // -61 tot -65 onderaan A
		     ra(stack_a);
	}
	count = 5;
	while (count--)
		rrb(stack_b); // -66 tot -70 op goeie plek zetten
	count = 5;
	while (count--)
	{
		rra(stack_a);
		pb(stack_a, stack_b); // -61 tot -65 op goeie plek zetten
	}
}

void	sort_low(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 15;
	while (count--) // -46 tot -60 op goeie plek zetten
	{
		rra(stack_a); // alles naar boven
		if ((*stack_a)->sorted_index < highest - 50) // -51 tot -60 op goeie plek zetten
		{
			pb(stack_a, stack_b); // -56 tot -60 staat goed
			if ((*stack_b)->sorted_index > highest - 56) // -51 tot -55 naar beneden
				rb(stack_b);
		}
	}
	count = 5;
	while (count--) // -51 tot -55 op goeie plek zetten
		rrb(stack_b);
	count = 5;
	while (count--) // -46 tot -50 op goeie plek zetten
		pb(stack_a, stack_b);
}

