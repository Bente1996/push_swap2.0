// final_list X2 ipv big_list

#include "push_swap.h"
#include <stdio.h>

void	sort_high_A(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 60;
	while (count > 30)
	{
		if ((*stack_b)->sorted_index > highest - 76) // -61 tot -75 onderaan A
			rb(stack_b);
		else                                       // -76 tot -90 bovenaan B
		{
			pa(stack_a, stack_b);
			if ((*stack_a)->sorted_index > highest - 86) // -76 tot -85 naar beneden, -86 tot -90 al goed!
				ra(stack_a);
		}
		count--;
	}
	while (count > 20) // -81 tot -85 op goeie plek zetten
	{
		rra(stack_a);
		if ((*stack_a)->sorted_index > highest - 81) // -76 tot -80 naar A
			pb(stack_a, stack_b);
		count--;
	}
	while (count > 15) // -76 tot -80 op goeie plek zetten
	{
		pa(stack_a, stack_b);
		count--;
	}
	while (count)
	{
		rrb(stack_b); // alles naaar boven
		count--;
	}
}

void	sort_medium_A(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 25;
	while (count > 10) // -61 tot -75 op goeie plek zetten
	{
		if ((*stack_b)->sorted_index < highest - 65) // -66 tot -75 naar B
		{
			pa(stack_a, stack_b);
			if ((*stack_a)->sorted_index > highest - 71) // -66 tot -70 onderaan B, -71 tot -75 op goeie plek
				ra(stack_a);
		}
		else // -61 tot -65 onderaan A
		     rb(stack_b);
		count--;
	}
	while (count > 5)
	{
		rra(stack_a); // -66 tot -70 op goeie plek zetten
		count--;
	}
	while (count)
	{
		rrb(stack_b);
		pa(stack_a, stack_b); // -61 tot -65 op goeie plek zetten
		count--;
	}
}

void	sort_low_A(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count = 15;
	while (count) // -46 tot -60 op goeie plek zetten
	{
		rrb(stack_b); // alles naar boven
		if ((*stack_b)->sorted_index < highest - 50) // -51 tot -60 op goeie plek zetten
		{
			pa(stack_a, stack_b); // -56 tot -60 staat goed
			if ((*stack_a)->sorted_index > highest - 56) // -51 tot -55 naar beneden
				ra(stack_a);
		}
		count--;
	}
	count = 5;
	while (count) // -51 tot -55 op goeie plek zetten
	{
		rra(stack_a);
		count--;
	}
	count = 5;
	while (count) // -46 tot -50 op goeie plek zetten
	{
		pa(stack_a, stack_b);
		count--;
	}
}


void	sort_rest_A(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 125;
	while (count > 80) // 45
	{
		rra(stack_a); // -31 tot -45 blijft in B
		count--;
		if ((*stack_a)->sorted_index > highest - 16) // begin: -1 tot -15
		{
			pb(stack_a, stack_b);
			rb(stack_b);
		}
		else if ((*stack_a)->sorted_index < highest - 15 && (*stack_a)->sorted_index > highest - 31) // -16 tot -30
			pb(stack_a, stack_b);
	}
	while (count > 65) // 15
	{
		if ((*stack_a)->sorted_index >= highest - 35) // -31 tot -35
		{
			pb(stack_a, stack_b);
			rb(stack_b);
		}
		else if ((*stack_a)->sorted_index >=highest - 40) // -36 tot -40
			ra(stack_a);
		else // -41 tot -45
		     pb(stack_a, stack_b);
		count--;
	}
	while (count > 60) // 5
	{
		pa(stack_a, stack_b); // -41 tot -45 goed
		count--;
	}
	while (count > 55) //5
	{
		rra(stack_a); // -36 tot -40 goed
		count--;
	}
	while (count > 50) // 5
	{
		rrb(stack_b);
		pa(stack_a, stack_b); // -30 tot -35 goed
		count--;
	}
	while (count > 35) // 15
	{
		if ((*stack_b)->sorted_index >= highest - 20)  // -16 tot -20
			rb(stack_b);
		else if ((*stack_b)->sorted_index >= highest - 25) // -21 tot -25
		{
			pa(stack_a, stack_b);
			ra(stack_a);
		}
		else // -26 tot -30
		     pa(stack_a, stack_b); // staat nu al goed
		count--;
	}
	while (count > 30) // 5
	{
		rra(stack_a); // -21 tot -25 goed
		count--;
	}
	while (count > 25) // 5
	{
		rrb(stack_b);
		pa(stack_a, stack_b); // -16 tot -20 goed
		count--;
	}
	while (count > 10) // 15
	{
		rrb(stack_b); // -1 tot -5
		if ((*stack_b)->sorted_index < highest - 5) // -11 tot -15 gelijk goed
		{
			pa(stack_a, stack_b);
			if ((*stack_a)->sorted_index >= highest - 10) // -6 tot -10
				ra(stack_a);
		}
		count--;
	}
	while (count > 5) // 5
	{
		rra(stack_a); // -6 tot -10 goed
		count--;
	}
	while (count) // 5
	{
		pa(stack_a, stack_b); // -1 tot -5 goed
		count--;
	}
}
int	split_A(t_node **stack_a, t_node **stack_b, int count, int highest) // kan hetzelfde als split_B worden gemaakt
{
	pb(stack_a, stack_b);
	if ((*stack_b)->sorted_index < highest && (*stack_b)->sorted_index > highest - 181) // 320-450
		count++; // count is nergens meer voor nodig
	else
		rb(stack_b); // 250-320 in B bewaren
	return (count);
}

void	devide_A(t_node **stack_a, t_node **stack_b, int half, int size)
{
	int	count;

	count = size;
	while (count)
	{
		if ((*stack_a)->sorted_index > half - (size - 44)) // -0 tot -135 naar beneden voor later (365-499)
			ra(stack_a);
		else if ((*stack_a)->sorted_index < half - (size - 30)) // -151 tot -180 bovenaan B (320-349) 
			pb(stack_a, stack_b);
		else                                             // -135 tot -150 onderaan B (350-364)
		{
			pb(stack_a,stack_b);
			rb(stack_b);
		}
		count--;
	}
	sort_high_A(stack_a, stack_b, half - (size - 90)); 
	sort_medium_A(stack_a, stack_b, half - (size -90)); 
	sort_low_A(stack_a, stack_b, half - (size - 90));
}

void	organise_A(t_node **stack_a, t_node **stack_b, int half)
{
	int count;

	devide_B(stack_a, stack_b, half, 180); // 0-135 beneden
	count = 135;
	while (count) // 135
	{
		rrb(stack_b);
		count--;
	}
	devide_B(stack_a, stack_b, half, 135); // 0-90 beneden
	count = 90;
	while (count) // 90
	{
		rrb(stack_b);
		count--;
	}
	devide_B(stack_a, stack_b, half, 90); // 45 beneden
	sort_rest(stack_a, stack_b, half); // sorteert laatste 45
}

void	sort_A(t_node **stack_a, t_node **stack_b, int half) // uitgecommened vanwege method 1 test, is wel goed!
{
	int	highest;
	int	count; // kan sowieso weg
	int	h;

	h = 250;
	highest = half;
	count = 0;
	while (h)
	{
		h--;
		count = split_A(stack_a, stack_b, count, highest); // houd 180 apart
	}
//	organise_B(stack_a, stack_b, half);
	organise_A(stack_a, stack_b, half);
}

void	final_list_A(t_node **stack_a, t_node **stack_b, int half, int count) // werkt normaal
{
	t_stats	*data;
	int	n;

	data = alloc_stats(stack_a, stack_b, half);
	if (!data)
		return ;
	int bente = 1000;
	data->lower--;
	data->lower--;
	while (count)
	{
		printf("data->lower: %d\n", data->lower);
		if (data->bottom_stack)
			printf("data->bottom: %d\n", data->bottom_stack->sorted_index);
		bente--;
		*stack_a = data->stack_a;
		n = find_case(data->stack_b->sorted_index, data->lower, data->bottom);
		if (n == 1)
		{
			printf("case one\n");
			case_one(data);
			count--;
		}
		else if (n == 2) // for -2, -3 en -4 (bottom <3)
		{
			printf("case one\n");
			case_two(data);
			count--;
		}
		else // rest
			rb(&data->stack_b);
	}
	printf("data->lower: %d\n", data->lower);
//	printf("data->lower: %d\n", data->lower);
	*stack_b = data->stack_b;
}
