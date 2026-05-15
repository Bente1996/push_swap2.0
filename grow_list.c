#include "push_swap.h"
#include <stdio.h>

void	grow_list(t_node **A, t_node **B, int half, int count) // werkt normaal
{
	t_stats	*data;
	int	n; // pas namen aan

	data = alloc_stats(A, B, half);
	if (!data)
		return ; // free en exit (1)
	while (count--)
	{
		n = find_case((*B)->n_index, data->lower, data->bottom); // goed
		if (n == 1)
			add_and_lower(data, A, B);
		else if (n == 2) // for -2, -3 en -4 (bottom <3)
			add(data, A, B);
		else // rest
		{
			rb(B, data->top);
			count++;
		}
	//	*stack_a = data->stack_a;
	//	*stack_b = data->stack_b;
	}
}
