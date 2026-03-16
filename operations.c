#include "push_swap.h"
#include <stddef.h>
#include <stdio.h>

int	pb(t_node **stack_a, t_node **stack_b)
{
	t_node	*tmp;

	tmp = *stack_a;
	*stack_a = (*stack_a)->next;
	tmp->next  = NULL; // losgekoppeld
	if (!*stack_b)
		*stack_b = tmp;
	else
	{
		tmp->next = *stack_b;
		*stack_b = tmp;
	}
	return (count_operations());
}
