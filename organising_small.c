#include "push_swap.h"

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
			if (((*stack_b)->sorted_index < half - 180))
					rb(stack_b);
		}
		else
			ra(stack_a);
	}
	sort_B(stack_a, stack_b, half);
}

void	sort_B(t_node **stack_a, t_node **stack_b, int half)
{
	int count;

	count = half - 135; // doe juist 115 rb ipv 135 rrb
	sort_quarter(stack_a, stack_b, half, 180); // 0-135 beneden
	while (count--)
		rb(stack_b);
	sort_quarter(stack_a, stack_b, half, 135); // 0-90 beneden
	count = 90; // van 90 naar 89 gedaan voor 499
	while (count--)
		rrb(stack_b);
	sort_quarter(stack_a, stack_b, half, 90); // 45 beneden
	sort_rest(stack_a, stack_b, half); // sorteert laatste
}

void	organise_A(t_node **stack_a, t_node **stack_b, int highest, int count)
{

	while (count--)
	{
		if ((*stack_a)->sorted_index < highest)
			pb(stack_a, stack_b);
		else
			ra(stack_a);
	}
	sort_A(stack_a, stack_b, highest);
}

