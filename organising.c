#include "push_swap.h"

void	organise_A(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = highest - 180;
	while (count--)
	{
		if ((*stack_a)->sorted_index < highest)
			pb(stack_a, stack_b);
		else
			ra(stack_a);
	}
	sort_A(stack_a, stack_b, highest);
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
			if (!((*stack_b)->sorted_index > half - 181)) // 181 voor 499 ipv 180
					rb(stack_b);
		}
		else
			ra(stack_a);
	}
	sort_B(stack_a, stack_b, half);
}

void	sort_A(t_node **stack_a, t_node **stack_b, int size)
{
	int count;

	count = 225;
	sort_quarter(stack_a, stack_b, size, 180); // 0-135 beneden
	while (count > 90) // 135
	{
		rrb(stack_b);
		count--;
	}
	sort_quarter(stack_a, stack_b, size, 135); // 0-90 beneden
	while (count--) // 90
		rrb(stack_b);
	sort_quarter(stack_a, stack_b, size, 90); // 45 beneden
	sort_rest(stack_a, stack_b, size); // sorteert laatste 45
}

void	sort_B(t_node **stack_a, t_node **stack_b, int half)
{
	int count;

	count = 115; // doe juist 115 rb ipv 135 rrb
	sort_quarter(stack_a, stack_b, half, 180); // 0-135 beneden
	while (count--)
		rb(stack_b);
	sort_quarter(stack_a, stack_b, half, 135); // 0-90 beneden
	count = 89; // van 90 naar 89 gedaan voor 499
	while (count--)
		rrb(stack_b);
	sort_quarter(stack_a, stack_b, half, 90); // 45 beneden
	sort_rest(stack_a, stack_b, half); // sorteert laatste 45
}
