#include "push_swap.h"
#include <stdio.h>

void	grow_list(t_node **stack_a, t_node **stack_b, int half, int count) // werkt normaal
{
	t_stats	*data;
	int	n;

	data = alloc_stats(stack_a, stack_b, half);
	if (!data)
		return ; // free en exit (1)
	while (count)
	{
		n = find_case(data->stack_b->sorted_index, data->lower, data->bottom);
		if (n == 1)
		{
			count--;
			case_one(data);
		}
		else if (n == 2) // for -2, -3 en -4 (bottom <3)
		{
			count--;
			case_two(data);
		}
		else // rest
			rb(&data->stack_b);
		*stack_a = data->stack_a;
		*stack_b = data->stack_b;
	}
}
