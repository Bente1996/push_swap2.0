/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   grow_list_utils.c                                       :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/08 17:37:27 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/08 17:37:29 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_group(int n_index, int lower, int bottom) // find case
{
	if (n_index == lower || n_index == lower - 1)
		return (1);
	else if ((n_index == lower - 2 || n_index == lower - 3 || n_index == lower - 4) && bottom < 3)
		return (2);
	else
		return (0);
}

void	grow_list(t_stats *data, t_node **a, t_node **b, int group)
{
	if (group == 1)
		grow_top(data, a, b);
	else if (group == 2)
		grow_bottom(data, a, b);
}

void	sort_bottom_stack(t_stats *data, t_node **a, t_node **b, int group) // omdraaien
{
	if (group == 1)
		grow_top(data, a, b); // omdraaien, andere func
	else if (group == 2)
		grow_bottom(data, a, b); // omdraaien, andere func
}

void	grow_top(t_stats *data, t_node **a, t_node **b) // add_and_lower
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

void	grow_bottom(t_stats *data, t_node **a, t_node **b) // add
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
