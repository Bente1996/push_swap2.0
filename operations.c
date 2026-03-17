#include "push_swap.h"
#include <stddef.h>
#include <stdio.h>

void	pb(t_node **stack_a, t_node **stack_b)
{
	t_node	*tmp;

	if (!*stack_a)
		return ;
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
	count_operations("pb");
}

void	pa(t_node **stack_a, t_node **stack_b)
{
	t_node	*tmp;

	if (!*stack_b)
		return ;
	tmp = *stack_b;
	*stack_b = (*stack_b)->next;
	tmp->next = NULL;
	if (!*stack_a)
		*stack_a = tmp;
	else
	{
		tmp->next = *stack_a;
		*stack_a = tmp;
	}
	count_operations("pa");
}

void	ra(t_node **stack_a)
{
	t_node	*first;
	t_node	*tmp;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	first = *stack_a;
	tmp = *stack_a;
	*stack_a = (*stack_a)->next; //nieuwe hoofd
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = first;
	first->next = NULL;// bij uiteinde 
	count_operations("ra");
}

void	rb(t_node **stack_b)
{
	t_node	*first;
	t_node	*tmp;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	first = *stack_b;
	tmp = *stack_b;
	*stack_b = (*stack_b)->next;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = first;
	first->next = NULL;
	count_operations("rb");
}
