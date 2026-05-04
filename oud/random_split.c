#include "push_swap.h"
#include <stdio.h>

void	split_A(t_node **stack_a, t_node **stack_b, int highest)
{
	if ((*stack_a)->sorted_index < highest && (*stack_a)->sorted_index > highest - 181) // 320-450
		pb(stack_a, stack_b);
	else
		ra(stack_a); // 250-320 in B bewaren
}

void	split_B(t_node **stack_b, int highest) // voor 180
{
	if (!((*stack_b)->sorted_index < highest && (*stack_b)->sorted_index > highest - 181)) // 70 tot 249
		rb(stack_b); // 0 tot 114 onderaan zodat rest (die we gaan groeperen) boven staat
}

void	organise_B(t_node **stack_a, t_node **stack_b, int half)
{
	int	h;

	h = half;
	while (h)
	{
		if ((*stack_a)->sorted_index < half)
		{
			pb(stack_a, stack_b);
			h--;
			split_B(stack_b, half); // houd 180 apart
		}
		else
			ra(stack_a);
	}
	sort_B(stack_a, stack_b, half);
}

void	sort_A(t_node **stack_a, t_node **stack_b, int half)
{
	int count;

	count = 225;
	sort_quarter(stack_a, stack_b, half, 180); // 0-135 beneden
	while (count > 90) // 135
	{
		rrb(stack_b);
		count--;
	}
	sort_quarter(stack_a, stack_b, half, 135); // 0-90 beneden
	while (count--) // 90
		rrb(stack_b);
	sort_quarter(stack_a, stack_b, half, 90); // 45 beneden
	sort_rest(stack_a, stack_b, half); // sorteert laatste 45
}

void	sort_B(t_node **stack_a, t_node **stack_b, int half)
{
	int count;

	count = 115; // doe juist 115 rb ipv 135 rrb
	sort_quarter(stack_a, stack_b, half, 180); // 0-135 beneden
	while (count--)
		rb(stack_b);
	sort_quarter(stack_a, stack_b, half, 135); // 0-90 beneden
	count = 90;
	while (count--)
		rrb(stack_b);
	sort_quarter(stack_a, stack_b, half, 90); // 45 beneden
	sort_rest(stack_a, stack_b, half); // sorteert laatste 45
}

void	organise_A(t_node **stack_a, t_node **stack_b, int half)
{
	int	h;

	h = 250;
	while (h--)
		split_A(stack_a, stack_b, half); // houd 180 apart
	sort_A(stack_a, stack_b, half);
}

void	sort_all(t_node **stack_a, t_node **stack_b, int half)
{
	int count;

	count = 70;
	organise_B(stack_a, stack_b, half); // organise afhangende van grootte, even/oneven getal
	organise_A(stack_a, stack_b, half + 180);
	final_list(stack_b, stack_a, half * 2, 70); // test met andere getallen, totaal 430+
	while (count--)
	{
		pa(stack_a, stack_b);
		if (stack_size(*stack_a))
			ra(stack_a);
	}
	final_list(stack_a, stack_b, half + 180, 180);
	final_list(stack_a, stack_b, half, 250);
}

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

void	sort_quarter(t_node **stack_a, t_node **stack_b, int half, int size) // bij 135
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
	sort_medium(stack_a, stack_b, half - (size - 90)); 
	sort_low(stack_a, stack_b, half - (size - 90));
}

void	sort_rest(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 45;
	while (count--) // 45
	{
		rrb(stack_b); // -31 tot -45 blijft in B
		if ((*stack_b)->sorted_index > highest - 16) // begin: -1 tot -15
		{
			pa(stack_a, stack_b);
			ra(stack_a);
		}
		else if ((*stack_b)->sorted_index < highest - 15 && (*stack_b)->sorted_index > highest - 31) // -16 tot -30
			pa(stack_a, stack_b);
	}
	count = 15;
	while (count--) // 15
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
		rra(stack_a);
		pb(stack_a, stack_b); // -30 tot -35 goed
	}
	count = 15;
	while (count--) // 15
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
	}
	count = 5;
	while (count--) // 5
		rrb(stack_b); // -21 tot -25 goed
	count = 5;
	while (count--) // 5
	{
		rra(stack_a);
		pb(stack_a, stack_b); // -16 tot -20 goed
	}
	count = 15;
	while (count--) // 15
	{
		rra(stack_a); // -1 tot -5
		if ((*stack_a)->sorted_index < highest - 5) // -11 tot -15 gelijk goed
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->sorted_index >= highest - 10) // -6 tot -10
				rb(stack_b);
		}
	}
	count = 5;
	while (count--) // 5
		rrb(stack_b); // -6 tot -10 goed
	count = 5;
	while (count--) // 5
		pb(stack_a, stack_b); // -1 tot -5 goed
}
