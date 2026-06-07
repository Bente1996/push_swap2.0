#include "push_swap.h"

int	find_case(int n_index, int lower, int bottom)
{
	if (n_index == lower || n_index == lower - 1)
		return (1);
	else if ((n_index == lower - 2 || n_index == lower - 3 || n_index == lower - 4) && bottom < 3)
		return (2);
	else
		return (0);
}

void	add_and_lower(t_stats *data, t_node **a, t_node **b)
{
	if ((*b)->n_index == data->lower - 1)
	{
		pa(a, b, data->top);
		data->swap++;
		data->lower++;
	}
	else if (data->swap) // lower met swap
	{
		pa(a, b, data->top);
		sa(a, data->top);
		data->swap = 0;
		if (data->bottom)
			handle_bottom(data, a);
		data->lower--; // toegevoegd
	}
	else // lower geen swap
	{
		pa(a, b, data->top);
		if (data->bottom)
			handle_bottom(data, a);
	}
	data->lower--;
}

void	add(t_stats *data, t_node **a, t_node **b)
{
	if (!data->bottom || data->bottom_stack->n_index < (*b)->n_index)
	{
		pa(a, b, data->top);
		ra(a, data->top);
		data->bottom_stack = find_bottom(*a);
	}
	else
	{
		pa(a, b, data->top);
		ra(a, data->top);
	}
	data->bottom++;
}
