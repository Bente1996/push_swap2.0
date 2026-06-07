#include "push_swap.h"
#include <stdio.h>

void	grow_list(t_node **a, t_node **b, int half, int count) // werkt normaal
{
	t_stats	*data;
	int	n; // pas namen aan

	data = alloc_stats(a, b, half);
	if (!data)
		return ; // free en exit (1)
	while (count--)
	{
		n = find_case((*b)->n_index, data->lower, data->bottom); // goed
		if (n == 1)
			add_and_lower(data, a, b);
		else if (n == 2) // for -2, -3 en -4 (bottom <3)
			add(data, a, b);
		else // rest
		{
			rb(b, data->top);
			count++;
		}
	}
}
