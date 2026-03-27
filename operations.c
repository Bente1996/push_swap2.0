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

void	rr(t_node **stack_a, t_node **stack_b)
{
	ra(stack_a);
	rb(stack_b);
//	count_operations("rr");
}

//void	rrb(t_node **stack_b)
//{
//	t_node	*tmp;
//	t_node *head;
//
//	head = *stack_b;
//	if (!(*stack_b)->next || !(*stack_b)->next->next) // voor hele kleine stacks
//		return ; // maak aparte functies voor de kleintjes
//	while ((*stack_b)->next->next)
//		*stack_b = (*stack_b)->next;
//	tmp = (*stack_b)->next->next;
//	(*stack_b)->next = NULL;
//	tmp->next = head;
//}
void	rrb(t_node **stack_b)
{
	t_node	*second_last;
	t_node	*last;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	second_last = *stack_b;
	last = *stack_b;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *stack_b;
	*stack_b = last;
//	count_operations("rrb");
}

void	rra(t_node **stack_a)
{
	t_node	*second_last;
	t_node	*last;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	second_last = *stack_a;
	last = *stack_a;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *stack_a;
	*stack_a = last;
//count_operations("rra");
}

void	sa(t_node **stack_a)
{
	t_node *first;
	t_node *second;
	
	if (!*stack_a || !(*stack_a)->next)
		return ;
	first = *stack_a;
	second = (*stack_a)->next;
	first->next = (*stack_a)->next->next;
	second->next = *stack_a;
	*stack_a = second;
	count_operations("sa");
}

void	sb(t_node **stack_b)
{
	t_node *first;
	t_node *second;
	
	if (!*stack_b || !(*stack_b)->next)
		return ;
	first = *stack_b;
	second = (*stack_b)->next;
	first->next = (*stack_b)->next->next;
	second->next = *stack_b;
	*stack_b = second;
	count_operations("sb");
}
