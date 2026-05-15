#include "push_swap.h"
#include <stddef.h>

bool	add_second(t_stats *data)
{
	if (data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1) // tweede mag ook
	{
		rra(&data->stack_a, data->top);
		data->bottom--;
		data->lower--;
		if (data->bottom)
			data->bottom_stack = find_bottom(data->stack_a);
		else
			data->bottom_stack = NULL;
		if (data->bottom && data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1)
		{
			rra(&data->stack_a, data->top);
			data->lower--;
			data->bottom_stack = NULL;
			data->bottom--;
		}
		return (true);
	}
	else
		return (false);
}

void	check_third(t_stats *data)
{
	data->lower--;
	data->bottom--;
	if (data->bottom && data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1) // maak ff 1 statement
	{
		rra(&data->stack_a, data->top);
		data->bottom_stack = NULL;
		data->bottom--;
		data->lower--;
	}
	else
		data->bottom_stack = NULL;
}

void	funk(t_stats *data)
{
	data->bottom--;
	data->lower--;
	if (data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1)
	{
		rra(&data->stack_a, data->top);
		data->bottom--;
		data->lower--;
		data->bottom_stack = NULL;
	}
}

void	get_third(t_stats *data)
{
	rra(&data->stack_a, data->top);
	sa(&data->stack_a, data->top);
	ra(&data->stack_a, data->top);
	sa(&data->stack_a, data->top);
	data->bottom_stack = find_bottom(data->stack_a);
	if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
		funk(data);
	else if (data->bottom_stack->sorted_index == data->stack_a->next->sorted_index - 1)
		fonk(data);
	else
	{
		if (data->stack_a->sorted_index > data->bottom_stack->sorted_index)
			data->bottom_stack = data->stack_a;
		ra(&data->stack_a, data->top);
	}
}

void	get_second(t_stats *data)
{
	rra(&data->stack_a, data->top);
	data->lower--;
	data->bottom--;
	sa(&data->stack_a, data->top);
	if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
	{
		data->lower--;
		data->bottom--;
		data->bottom_stack = NULL;
	}
	else
	{
		ra(&data->stack_a, data->top);
		data->bottom_stack = find_bottom(data->stack_a);
	}
}

void	fonk(t_stats *data)
{
	rra(&data->stack_a, data->top);
	sa(&data->stack_a, data->top);
	data->lower--;
	data->bottom--;
	if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
	{
		data->bottom--;
		data->lower--;
		data->bottom_stack = NULL;
	}
	else
	{
		ra(&data->stack_a, data->top);
		data->bottom_stack = find_bottom(data->stack_a);
	}
}

