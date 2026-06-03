#include "push_swap.h"

void	sort_big_list(t_node **A, t_node **B, int all, int size)
{
	int	sorted;
	int	half;

	half = all / 2;
	sorted = half - size;
	organise_B(A, B, half, size);
	organise_A(A, B, all, half + size);
	if (all % 2)
	{
		grow_list(B, A, all, half - size + 1);
		sorted++;
	}
	else
		grow_list(B, A, all, half - size);
	while (sorted--)
	{
		pa(A, B, 0);
		if (*A)
			ra(A, 0);
	}
	grow_list(A, B, half + size, size);
	grow_list(A, B, half, half);
}
