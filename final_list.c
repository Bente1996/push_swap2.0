#include "push_swap.h"
#include <stdio.h>

void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter)
{
	t_node	*bottom_stack;
	int	lower;
	int	swap;
	int	bottom;

	lower = half + 1;
	swap = 0;
	bottom = 0;
	bottom_stack = NULL;
	while (half > quarter)
	{
		rrb(stack_b);
		pa(stack_a, stack_b);
		half--;
	}
	while (half)
	{
		pa(stack_a, stack_b);
		half--;
	}
	int n = 1000;
	while (*stack_b && n)
	{
		printf("stack_B: %d\n", (*stack_b)->sorted_index);
		printf("lower: %d\n", lower);
		if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1)
		{
			if ((*stack_b)->sorted_index == lower - 1)
			{
				pa(stack_a, stack_b);
				swap++;
				lower++;
			}
			else if (swap)
			{
				pa(stack_a, stack_b);
				sa(stack_a);
				swap = 0;
				if (bottom)
				{
					rra(stack_a);
					bottom = 0;
					bottom_stack = NULL;
					lower--;
				}
				lower--;
			}
			else
			{
				pa(stack_a, stack_b);
				if (bottom && bottom_stack->sorted_index == (*stack_a)->sorted_index - 1)
				{
					rra(stack_a);
					bottom = 0;
					bottom_stack = NULL;
					lower--;
				}
			}
			lower--;
		}
		else if ((*stack_b)->sorted_index == lower - 2 && !bottom)
		{
			pa(stack_a, stack_b);
			ra(stack_a);
			bottom = 1;
			bottom_stack = find_bottom(*stack_a);
		}
		else
			rb(stack_b);
		n--;
	}
}
