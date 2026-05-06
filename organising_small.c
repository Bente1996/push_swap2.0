#include "push_swap.h"

void	organise_B_small(t_node **stack_a, t_node **stack_b, int half, int size)
{
	int	h;

	h = half;
	while (h)
	{
		if ((*stack_a)->sorted_index < half)
		{
			pb(stack_a, stack_b);
			h--;
			if (((*stack_b)->sorted_index < half - size))
					rb(stack_b);
		}
		else
			ra(stack_a);
	}
	sort_B_small(stack_a, stack_b, half, size);
}

void	sort_B_small(t_node **stack_a, t_node **stack_b, int half, int size)
{
	int count;

	count = 45; // doe juist 115 rb ipv 135 rrb
	sort_quarter(stack_a, stack_b, half, size); // 0-135 beneden
	if (size >= 135)
	{
		if (size == 180)
			count += 70;
		while (count--)
			rb(stack_b);
		sort_quarter(stack_a, stack_b, half, size - 45); // 0-90 beneden
	}
	if (size == 180)
	{
		count = 90; // van 90 naar 89 gedaan voor 499
		while (count--)
			rrb(stack_b);
		sort_quarter(stack_a, stack_b, half, 90); // 45 beneden
	}
	sort_rest(stack_a, stack_b, half); // sorteert laatste
}

#include <stdio.h>

void	organise_A_small(t_node **stack_a, t_node **stack_b, int highest, int half)
{
	int	size;

	size = highest - half;
	while (half--)
	{
		if ((*stack_a)->sorted_index < highest)
			pb(stack_a, stack_b);
		else
			ra(stack_a);
	}
	sort_A_small(stack_a, stack_b, highest, size);
}

void	sort_A_small(t_node **stack_a, t_node **stack_b, int highest, int size)
{
	int count;

	count = 90;
   	sort_quarter(stack_a, stack_b, highest, size); // 0-135 beneden
	if (size >= 135)
	{
		if (size == 180)
			count += 45;
		while (count--) // 135
			rrb(stack_b);
		sort_quarter(stack_a, stack_b, highest, size - 45); // 0-90 beneden
	}
	if (size == 180)
	{
		count = 90;
		while (count--) // 90
			rrb(stack_b);
		sort_quarter(stack_a, stack_b, highest, 90); // 45 beneden
	}
	sort_rest(stack_a, stack_b, highest); // sorteert laatste 45
}
