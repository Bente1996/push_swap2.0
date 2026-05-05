#include "push_swap.h"

int	find_case(int sorted_index, int lower, int bottom)
{
	if (sorted_index == lower || sorted_index == lower - 1)
		return (1);
	else if ((sorted_index == lower - 2 || sorted_index == lower - 3 || sorted_index == lower - 4) && bottom < 3)
		return (2);
	else
		return (0);
}

void	add_and_lower(t_stats *data)
{
	if (data->stack_b->sorted_index == data->lower - 1)
	{
		pa(&data->stack_a, &data->stack_b);
		data->swap++;
		data->lower++;
	}
	else if (data->swap) // lower met swap
	{
		pa(&data->stack_a, &data->stack_b);
		sa(&data->stack_a);
		data->swap = 0;
		if (data->bottom)
			handle_bottom(data);
		data->lower--; // toegevoegd
	}
	else // lower geen swap
	{
		pa(&data->stack_a, &data->stack_b);
		if (data->bottom)
			handle_bottom(data); // zelfde als boven miscchien?
	}
	data->lower--;
}

void	add(t_stats *data)
{
	if (!data->bottom || data->bottom_stack->sorted_index < data->stack_b->sorted_index)
	{
		pa(&data->stack_a, &data->stack_b);
		ra(&data->stack_a);
		data->bottom_stack = find_bottom(data->stack_a);
	}
	else
	{
		pa(&data->stack_a, &data->stack_b);
		ra(&data->stack_a);
	}
	data->bottom++;
}
