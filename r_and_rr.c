#include "push_swap.h"
#include <stddef.h>

void	ra(t_node **A, int top)
{
	t_node	*first;
	t_node	*tmp;

	if (!*A || !(*A)->next)
		return ;
	if (top)
	{
		rb(A, top - 1);
		return ;
	}
	first = *A;
	tmp = *A;
	*A = (*A)->next; //nieuwe hoofd
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = first;
	first->next = NULL;// bij uiteinde 
	count_operations("ra");
}

void	rb(t_node **B, int top)
{
	t_node	*first;
	t_node	*tmp;

	if (!*B || !(*B)->next)
		return ;
	if (top)
	{
		ra(B, top - 1);
		return ;
	}
	first = *B;
	tmp = *B;
	*B = (*B)->next;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = first;
	first->next = NULL;
	count_operations("rb");
}

void	rra(t_node **A, int top)
{
	t_node	*second_last;
	t_node	*last;

	if (!*A || !(*A)->next)
		return ;
	if (top)
	{
		rrb(A);
		return ;
	}
	second_last = *A;
	last = *A;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *A;
	*A = last;
	count_operations("rra");
}

void	rrb(t_node **B)
{
	t_node	*second_last;
	t_node	*last;

	if (!*B || !(*B)->next)
		return ;
	second_last = *B;
	last = *B;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *B;
	*B = last;
	count_operations("rrb");
}
