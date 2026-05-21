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

void	add_and_lower(t_stats *data, t_node **A, t_node **B)
{
	if ((*B)->n_index == data->lower - 1)
	{
		pa(A, B, data->top);
		data->swap++;
		data->lower++;
	}
	else if (data->swap) // lower met swap
	{
		pa(A, B, data->top);
		sa(A, data->top);
		data->swap = 0;
		if (data->bottom)
			handle_bottom(data, A);
		data->lower--; // toegevoegd
	}
	else // lower geen swap
	{
		pa(A, B, data->top);
		if (data->bottom)
			handle_bottom(data, A); // zelfde als boven miscchien?
	}
	data->lower--;
}

void	add(t_stats *data, t_node **A, t_node **B)
{
	if (!data->bottom || data->bottom_stack->n_index < (*B)->n_index)
	{
		pa(A, B, data->top);
		ra(A, data->top);
		data->bottom_stack = find_bottom(*A);
	}
	else
	{
		pa(A, B, data->top);
		ra(A, data->top);
	}
	data->bottom++;
}
