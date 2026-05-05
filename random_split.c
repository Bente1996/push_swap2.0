#include "push_swap.h"
#include <stdio.h>

void	split_A(t_node **stack_a, t_node **stack_b, int size)
{
	if ((*stack_a)->sorted_index < size)
		pb(stack_a, stack_b);
	else
		ra(stack_a); // hoogste 70
}

void	split_B(t_node **stack_b, int size) // voor 180
{
	if (!((*stack_b)->sorted_index > size)) // 70 tot 249
		rb(stack_b); // 0 tot 114 onderaan zodat rest (die we gaan groeperen) boven staat
}
