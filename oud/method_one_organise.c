#include "push_swap.h"
#include <stdio.h>


void	split_list(t_node **stack_a, t_node **stack_b, int half) // uitgecommened vanwege method 1 test, is wel goed!
{
	int	highest;
	int	count; // kan sowieso weg
	int	h;

	h = half;
	highest = half;
	count = 0;
	while (h)
	{
		if ((*stack_a)->sorted_index < half)
		{
			pb(stack_a, stack_b);
			h--;
			count = split_B(stack_b, count, highest); // houd 216 apart
		}
		else
			ra(stack_a);
	}
	organise_B(stack_a, stack_b, half);
}

int	split_B(t_node **stack_b, int count, int highest) // 0-33 onderaan B
{
	if ((*stack_b)->sorted_index < highest && (*stack_b)->sorted_index > highest - 217) // 34 tot 249
		count++;
	else
		rb(stack_b); // 0 tot 33 onderaan zodat rest (die we gaan groeperen) boven staat
	return (count);
}

void	organise_B(t_node **stack_a, t_node **stack_b, int half)
{
	int count;

	count = 196;
	devide_B(stack_a, stack_b, half, 216); // 0-135 beneden
	while (count > 108)
	{
		rb(stack_b);
		count--;
	}
	devide_B(stack_a, stack_b, half, 162); // 0-90 beneden
	while (count)
	{
		rrb(stack_b);
		count--;
	}
	devide_B(stack_a, stack_b, half, 108); // 45 beneden
	sort_rest(stack_a, stack_b, half); // sorteert laatste 45

}

void	sort_all(t_node **stack_a, t_node **stack_b, int half) // 180 werkend
{
	split_list(stack_a, stack_b, half); // split en houdt 135 apart, 115-249 bovenaan B
	big_list(stack_a, stack_b, --half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
//	final_list(stack_a, stack_b, half, half / 2);
	
}

void	sort_high(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 72;
	while (count > 36)
	{
		if ((*stack_a)->sorted_index > highest - 91) // -61 tot -75 onderaan A
			ra(stack_a);
		else                                       // -76 tot -90 bovenaan B
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->sorted_index > highest - 103) // -76 tot -85 naar beneden, -86 tot -90 al goed!
				rb(stack_b);
		}
		count--;
	}
	while (count > 24) // -81 tot -85 op goeie plek zetten
	{
		rrb(stack_b);
		if ((*stack_b)->sorted_index > highest - 97) // -76 tot -80 naar A
			pa(stack_a, stack_b);
		count--;
	}
	while (count > 18) // -76 tot -80 op goeie plek zetten
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

	count = 30;
	while (count > 12) // -61 tot -75 op goeie plek zetten
	{
		if ((*stack_a)->sorted_index < highest - 78) // -66 tot -75 naar B
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->sorted_index > highest - 85) // -66 tot -70 onderaan B, -71 tot -75 op goeie plek
				rb(stack_b);
		}
		else // -61 tot -65 onderaan A
		     ra(stack_a);
		count--;
	}
	while (count > 6)
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
	int	count = 18;
	while (count) // -46 tot -60 op goeie plek zetten
	{
		rra(stack_a); // alles naar boven
		if ((*stack_a)->sorted_index < highest - 60) // -51 tot -60 op goeie plek zetten
		{
			pb(stack_a, stack_b); // -56 tot -60 staat goed
			if ((*stack_b)->sorted_index > highest - 67) // -51 tot -55 naar beneden
				rb(stack_b);
		}
		count--;
	}
	count = 6;
	while (count) // -51 tot -55 op goeie plek zetten
	{
		rrb(stack_b);
		count--;
	}
	count = 6;
	while (count) // -46 tot -50 op goeie plek zetten
	{
		pb(stack_a, stack_b);
		count--;
	}
}

void	devide_B(t_node **stack_a, t_node **stack_b, int half, int size) // bij 216
{
	printf("size:%d\n", size);
	printf("half:%d\n", half);
	int	count;

	count = size;
	while (count)
	{
		if ((*stack_b)->sorted_index > half - (size - 53)) // -0 tot -162 naar beneden voor later (87-249)
			rb(stack_b);
		else if ((*stack_b)->sorted_index < half - (size - 36)) // -110 tot -145 bovenaan A (34 - 68)
			pa(stack_a, stack_b);
		else                                             // -163 tot -145 onderaan A (69 - 86)
		{
			pa(stack_a,stack_b);
			ra(stack_a);
		}
		count--;
	}
	sort_high(stack_a, stack_b, half - (size - 108)); 
	sort_medium(stack_a, stack_b, half - (size -108)); 
	sort_low(stack_a, stack_b, half - (size - 108));
}

void	sort_rest(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 150;
	while (count > 96) // 45
	{
		rrb(stack_b); // -31 tot -45 blijft in B
		count--;
		if ((*stack_b)->sorted_index > highest - 19) // begin: -1 tot -15
		{
			pa(stack_a, stack_b);
			ra(stack_a);
		}
		else if ((*stack_b)->sorted_index < highest - 18 && (*stack_b)->sorted_index > highest - 37) // -16 tot -30
			pa(stack_a, stack_b);
	}
	while (count > 78) // 15
	{
		if ((*stack_b)->sorted_index >= highest - 42) // -31 tot -35
		{
			pa(stack_a, stack_b);
			ra(stack_a);
		}
		else if ((*stack_b)->sorted_index >=highest - 48) // -36 tot -40
			rb(stack_b);
		else // -41 tot -45
		     pa(stack_a, stack_b);
		count--;
	}
	while (count > 72) // 5
	{
		pb(stack_a, stack_b); // -41 tot -45 goed
		count--;
	}
	while (count > 66) //5
	{
		rrb(stack_b); // -36 tot -40 goed
		count--;
	}
	while (count > 60) // 5
	{
		rra(stack_a);
		pb(stack_a, stack_b); // -30 tot -35 goed
		count--;
	}
	while (count > 42) // 15
	{
		if ((*stack_a)->sorted_index >= highest - 24)  // -16 tot -20
			ra(stack_a);
		else if ((*stack_a)->sorted_index >= highest - 30) // -21 tot -25
		{
			pb(stack_a, stack_b);
			rb(stack_b);
		}
		else // -26 tot -30
		     pb(stack_a, stack_b); // staat nu al goed
		count--;
	}
	while (count > 36) // 5
	{
		rrb(stack_b); // -21 tot -25 goed
		count--;
	}
	while (count > 30) // 5
	{
		rra(stack_a);
		pb(stack_a, stack_b); // -16 tot -20 goed
		count--;
	}
	while (count > 12) // 15
	{
		rra(stack_a); // -1 tot -5
		if ((*stack_a)->sorted_index < highest - 6) // -11 tot -15 gelijk goed
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->sorted_index >= highest - 12) // -6 tot -10
				rb(stack_b);
		}
		count--;
	}
	while (count > 6) // 5
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
