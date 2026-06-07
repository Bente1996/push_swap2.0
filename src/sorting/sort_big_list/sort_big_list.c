#include "push_swap.h"

void	sort_big_list(t_node **a, t_node **b, int all, int size)
{
	int	sorted;
	int	half;

	half = all / 2;
	sorted = half - size;
	organise_b(a, b, half, size);
	organise_a(a, b, all, half + size);
	if (all % 2)
	{
		grow_list(b, a, all, half - size + 1);
		sorted++;
	}
	else
		grow_list(b, a, all, half - size);
	while (sorted--)
	{
		pa(a, b, 0);
		if (*a)
			ra(a, 0);
	}
	grow_list(a, b, half + size, size);
	grow_list(a, b, half, half);
}
