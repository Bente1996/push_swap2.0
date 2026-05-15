#include "push_swap.h"
#include <stddef.h>

void	handle_bottom(t_stats *data)
{
	if (data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1) // wanneer er iig 1 naar boven moet
	{
		rra(&data->stack_a, data->top);
		data->bottom--;
		data->lower--;
		if (data->bottom)
			more_bottom(data);
		else
			data->bottom_stack = NULL;
	}
}

void	more_bottom(t_stats *data)
{
	if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1) // eerste was goed
	{
		data->bottom_stack = find_bottom(data->stack_a);
		if (!add_second(data) && data->bottom == 2) // check tweede
				try_three(data); // tweede mag niet, probeer derde
	}
	else // eerste was niet goed dus probeer tweede
		 try_two(data);
}

void	try_three(t_stats *data)
{
	data->bottom_stack = check_bottom(data->stack_a);
	if (data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1)
	{
		rra(&data->stack_a, data->top);
		rra(&data->stack_a, data->top);
		sa(&data->stack_a, data->top);
		data->lower--;
		data->bottom--;
	}
	if (data->stack_a->sorted_index != data->stack_a->next->sorted_index - 1)
	{
		ra(&data->stack_a, data->top);
		data->bottom_stack = find_bottom(data->stack_a);
	}
	else
	{
		data->bottom--;
		data->bottom_stack = NULL;
		data->lower--;
	}
}

void	try_two(t_stats *data)
{
	rra(&data->stack_a, data->top);
	if (data->bottom == 2)
		data->bottom_stack = find_bottom(data->stack_a);
	else
		data->bottom_stack = data->stack_a->next;
	if (data->stack_a->sorted_index == data->stack_a->next->next->sorted_index - 1) // als tweede goed is
	{
		sa(&data->stack_a, data->top);
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1) // twee op juiste plek
			check_third(data);
		else if (data->bottom_stack->sorted_index == data->stack_a->next->sorted_index - 1) // niet twee juiste volgorde
			get_second(data);
		else // tweede was niet goed
		     ra(&data->stack_a, data->top);
	}
	else // tweede was niet goed, dus moet derde wel zijn
		 get_third(data);
}


