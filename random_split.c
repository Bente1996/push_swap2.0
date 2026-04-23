#include "push_swap.h"
#include <stdio.h>

int	split_B(t_node **stack_b, int count, int highest) // voor 180
{
	if ((*stack_b)->sorted_index < highest && (*stack_b)->sorted_index > highest - 181) // 70 tot 249
		count++;
	else
		rb(stack_b); // 0 tot 114 onderaan zodat rest (die we gaan groeperen) boven staat
	return (count);
}

void	split_list(t_node **stack_a, t_node **stack_b, int half)
{
	int	highest;
	int	count; // kan sowieso weg
	int	h;

	h = half;
	highest = half;
	count = 0;
	while (h)
	{
		if ((*stack_a)->sorted_index < half) // voeg s toe: NEE geprobeerd
		{
			pb(stack_a, stack_b);
			h--;
			count = split_B(stack_b, count, highest); // houd 180 apart
		}
		else
			ra(stack_a);
	}
	organise_B(stack_a, stack_b, half);
}

void	organise_B(t_node **stack_a, t_node **stack_b, int half)
{
	int count;

	count = 205; // doe juist 115 rb ipv 135 rrb
	devide_B(stack_a, stack_b, half, 180); // 0-135 beneden
	while (count > 90)
	{
		rb(stack_b);
		count--;
	}
	devide_B(stack_a, stack_b, half, 135); // 0-90 beneden
	while (count)
	{
		rrb(stack_b);
		count--;
	}
	devide_B(stack_a, stack_b, half, 90); // 45 beneden
	sort_rest(stack_a, stack_b, half); // sorteert laatste 45

}

void	sort_all(t_node **stack_a, t_node **stack_b, int half) // 180 werkend
{

	split_list(stack_a, stack_b, half); // split en houdt 135 apart, 115-249 bovenaan B
	big_list(stack_a, stack_b, --half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
	final_list(stack_a, stack_b, half, half / 2);
	
}

void	sort_high(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 60;
	while (count > 30)
	{
		if ((*stack_a)->sorted_index > highest - 76) // -61 tot -75 onderaan A
			ra(stack_a);
		else                                       // -76 tot -90 bovenaan B
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->sorted_index > highest - 86) // -76 tot -85 naar beneden, -86 tot -90 al goed!
				rb(stack_b);
		}
		count--;
	}
	while (count > 20) // -81 tot -85 op goeie plek zetten
	{
		rrb(stack_b);
		if ((*stack_b)->sorted_index > highest - 81) // -76 tot -80 naar A
			pa(stack_a, stack_b);
		count--;
	}
	while (count > 15) // -76 tot -80 op goeie plek zetten
	{
		pb(stack_a, stack_b);
		count--;
	}
	while (count)
	{
		rra(stack_a); // alles naaar boven
		count--;
	}
}

void	sort_medium(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 25;
	while (count > 10) // -61 tot -75 op goeie plek zetten
	{
		if ((*stack_a)->sorted_index < highest - 65) // -66 tot -75 naar B
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->sorted_index > highest - 71) // -66 tot -70 onderaan B, -71 tot -75 op goeie plek
				rb(stack_b);
		}
		else // -61 tot -65 onderaan A
		     ra(stack_a);
		count--;
	}
	while (count > 5)
	{
		rrb(stack_b); // -66 tot -70 op goeie plek zetten
		count--;
	}
	while (count)
	{
		rra(stack_a);
		pb(stack_a, stack_b); // -61 tot -65 op goeie plek zetten
		count--;
	}
}

void	sort_low(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count = 15;
	while (count) // -46 tot -60 op goeie plek zetten
	{
		rra(stack_a); // alles naar boven
		if ((*stack_a)->sorted_index < highest - 50) // -51 tot -60 op goeie plek zetten
		{
			pb(stack_a, stack_b); // -56 tot -60 staat goed
			if ((*stack_b)->sorted_index > highest - 56) // -51 tot -55 naar beneden
				rb(stack_b);
		}
		count--;
	}
	count = 5;
	while (count) // -51 tot -55 op goeie plek zetten
	{
		rrb(stack_b);
		count--;
	}
	count = 5;
	while (count) // -46 tot -50 op goeie plek zetten
	{
		pb(stack_a, stack_b);
		count--;
	}
}

void	devide_B(t_node **stack_a, t_node **stack_b, int half, int size) // bij 135
{
	int	count;

	count = size;
	while (count)
	{
		if ((*stack_b)->sorted_index > half - (size - 44)) // -0 tot -90 naar beneden voor later (160-249)
			rb(stack_b);
		else if ((*stack_b)->sorted_index < half - (size - 30)) // -106 tot -135 bovenaan A (115-145)
			pa(stack_a, stack_b);
		else                                             // -90 tot -105 onderaan A (145-160)
		{
			pa(stack_a,stack_b);
			ra(stack_a);
		}
		count--;
	}
	sort_high(stack_a, stack_b, half - (size - 90)); 
	sort_medium(stack_a, stack_b, half - (size -90)); 
	sort_low(stack_a, stack_b, half - (size - 90));
}

void	sort_rest(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 125;
	while (count > 80) // 45
	{
		rrb(stack_b); // -31 tot -45 blijft in B
		count--;
		if ((*stack_b)->sorted_index > highest - 16) // begin: -1 tot -15
		{
			pa(stack_a, stack_b);
			ra(stack_a);
		}
		else if ((*stack_b)->sorted_index < highest - 15 && (*stack_b)->sorted_index > highest - 31) // -16 tot -30
			pa(stack_a, stack_b);
	}
	while (count > 65) // 15
	{
		if ((*stack_b)->sorted_index >= highest - 35) // -31 tot -35
		{
			pa(stack_a, stack_b);
			ra(stack_a);
		}
		else if ((*stack_b)->sorted_index >=highest - 40) // -36 tot -40
			rb(stack_b);
		else // -41 tot -45
		     pa(stack_a, stack_b);
		count--;
	}
	while (count > 60) // 5
	{
		pb(stack_a, stack_b); // -41 tot -45 goed
		count--;
	}
	while (count > 55) //5
	{
		rrb(stack_b); // -36 tot -40 goed
		count--;
	}
	while (count > 50) // 5
	{
		rra(stack_a);
		pb(stack_a, stack_b); // -30 tot -35 goed
		count--;
	}
	while (count > 35) // 15
	{
		if ((*stack_a)->sorted_index >= highest - 20)  // -16 tot -20
			ra(stack_a);
		else if ((*stack_a)->sorted_index >= highest - 25) // -21 tot -25
		{
			pb(stack_a, stack_b);
			rb(stack_b);
		}
		else // -26 tot -30
		     pb(stack_a, stack_b); // staat nu al goed
		count--;
	}
	while (count > 30) // 5
	{
		rrb(stack_b); // -21 tot -25 goed
		count--;
	}
	while (count > 25) // 5
	{
		rra(stack_a);
		pb(stack_a, stack_b); // -16 tot -20 goed
		count--;
	}
	while (count > 10) // 15
	{
		rra(stack_a); // -1 tot -5
		if ((*stack_a)->sorted_index < highest - 5) // -11 tot -15 gelijk goed
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->sorted_index >= highest - 10) // -6 tot -10
				rb(stack_b);
		}
		count--;
	}
	while (count > 5) // 5
	{
		rrb(stack_b); // -6 tot -10 goed
		count--;
	}
	while (count) // 5
	{
		pb(stack_a, stack_b); // -1 tot -5 goed
		count--;
	}
}
