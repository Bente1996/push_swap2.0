#include "push_swap.h"
#include <stddef.h>

bool	add_second(t_stats *data, t_node **A)
{
	if (data->bottom_stack->n_index == (*A)->n_index - 1) // tweede mag ook
	{
		rra(A, data->top);
		data->bottom--;
		data->lower--;
		if (data->bottom)
			data->bottom_stack = find_bottom(*A);
		else
			data->bottom_stack = NULL;
		if (data->bottom && data->bottom_stack->n_index == (*A)->n_index - 1)
		{
			rra(A, data->top);
			data->lower--;
			data->bottom_stack = NULL;
			data->bottom--;
		}
		return (true);
	}
	else
		return (false);
}

void	check_third(t_stats *data, t_node **A)
{
	data->lower--;
	data->bottom--;
	if (data->bottom && data->bottom_stack->n_index == (*A)->n_index - 1) // maak ff 1 statement
	{
		rra(A, data->top);
		data->bottom_stack = NULL;
		data->bottom--;
		data->lower--;
	}
	else
		data->bottom_stack = NULL;
}

void	funk(t_stats *data, t_node **A)
{
	data->bottom--;
	data->lower--;
	if (data->bottom_stack->n_index == (*A)->n_index - 1)
	{
		rra(A, data->top);
		data->bottom--;
		data->lower--;
		data->bottom_stack = NULL;
	}
}

void	get_third(t_stats *data, t_node **A)
{
	rra(A, data->top);
	sa(A, data->top);
	ra(A, data->top);
	sa(A, data->top);
	data->bottom_stack = find_bottom(*A);
	if ((*A)->n_index == (*A)->next->n_index - 1)
		funk(data, A);
	else if (data->bottom_stack->n_index == (*A)->next->n_index - 1)
		fonk(data, A);
	else
	{
		if ((*A)->n_index > data->bottom_stack->n_index)
			data->bottom_stack = *A;
		ra(A, data->top);
	}
}

void	get_second(t_stats *data, t_node **A)
{
	rra(A, data->top);
	data->lower--;
	data->bottom--;
	sa(A, data->top);
	if ((*A)->n_index == (*A)->next->n_index - 1)
	{
		data->lower--;
		data->bottom--;
		data->bottom_stack = NULL;
	}
	else
	{
		ra(A, data->top);
		data->bottom_stack = find_bottom(*A);
	}
}

void	fonk(t_stats *data, t_node **A)
{
	rra(A, data->top);
	sa(A, data->top);
	data->lower--;
	data->bottom--;
	if ((*A)->n_index == (*A)->next->n_index - 1)
	{
		data->bottom--;
		data->lower--;
		data->bottom_stack = NULL;
	}
	else
	{
		ra(A, data->top);
		data->bottom_stack = find_bottom(*A);
	}
}

