#include "push_swap.h"

void	organise_B(t_node **A, t_node **B, int half, int size)
{
	int	h;

	h = half;
	while (h)
	{
		if ((*A)->n_index < half)
		{
			pb(A, B);
			h--;
			if (((*B)->n_index < half - size))
					rb(B, 0);
		}
		else
			ra(A, 0);
	}
	sort_B(A, B, half, size);
}

void	sort_B(t_node **A, t_node **B, int half, int size)
{
	int count;

	count = half - size + 45;
	sort_forty_five(A, B, half, size); // 0-135 beneden
	if (size >= 135)
	{
		while (count--)
			rb(B, 0);
		sort_forty_five(A, B, half, size - 45); // 0-90 beneden
	}
	if (size == 180)
	{
		count = 90; // van 90 naar 89 gedaan voor 499
		while (count--)
			rrb(B);
		sort_forty_five(A, B, half, 90); // 45 beneden
	}
	if (size >= 90)
		sort_rest(A, B, half); // sorteert laatste
}

void	organise_A(t_node **A, t_node **B, int all, int highest)
{
	int	size;
	int	half;

	half = all / 2;
	size = highest - half;
	if (all % 2)
		half++;
	while (half--)
	{
		if ((*A)->n_index < highest)
			pb(A, B);
		else
			ra(A, 0);
	}
	sort_A(A, B, highest, size);
}

void	sort_A(t_node **A, t_node **B, int highest, int size)
{
	int count;

	count = 90;
	sort_forty_five(A, B, highest, size); // 0-135 beneden
	if (size >= 135)
	{
		if (size == 180)
			count += 45;
		while (count--) // 135
			rrb(B);
		sort_forty_five(A, B, highest, size - 45); // 0-90 beneden
	}
	if (size == 180)
	{
		count = 90;
		while (count--) // 90
			rrb(B);
		sort_forty_five(A, B, highest, 90); // 45 beneden
	}
	if (size >= 90)
		sort_rest(A, B, highest); // sorteert laatste 45
}
