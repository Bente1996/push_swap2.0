#include "push_swap.h"
#include <stddef.h>

void	pa(t_node **A, t_node **B, int top)
{
	t_node	*tmp;

	if (!*B)
		return ;
	if (top)
	{
		pb(B, A);
		return ;
	}
	tmp = *B;
	*B = (*B)->next;
	tmp->next = NULL;
	if (!*A)
		*A = tmp;
	else
	{
		tmp->next = *A;
		*A = tmp;
	}
	count_operations("pa");
}

void	pb(t_node **A, t_node **B)
{
	t_node	*tmp;

	if (!*A)
		return ;
	tmp = *A;
	*A = (*A)->next;
	tmp->next  = NULL; // losgekoppeld
	if (!*B)
		*B = tmp;
	else
	{
		tmp->next = *B;
		*B = tmp;
	}
	count_operations("pb");
}

void	sa(t_node **A, int top)
{
	t_node *first;
	t_node *second;
	
	if (!*A || !(*A)->next)
		return ;
	if (top)
	{
		sb(A);
		return ;
	}
	first = *A;
	second = (*A)->next;
	first->next = (*A)->next->next;
	second->next = *A;
	*A = second;
	count_operations("sa");
}

void	sb(t_node **B)
{
	t_node *first;
	t_node *second;
	
	if (!*B || !(*B)->next)
		return ;
	first = *B;
	second = (*B)->next;
	first->next = (*B)->next->next;
	second->next = *B;
	*B = second;
	count_operations("sb");
}
