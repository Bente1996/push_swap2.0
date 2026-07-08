/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   grow_top.c                                              :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/09 19:42:20 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/09 19:42:48 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

void	move_to_top(t_stats *data, t_node **a, t_node **b)
{
	pa(a, b);
	if ((*a)->n_index == data->lower - 1)
		data->swap++;
	else
		add_one(data, a);
	if (data->bottom && data->bottom_stack->n_index == data->lower)
		add_more(data, a);
}

void	add_one(t_stats *data, t_node **a)
{
	data->lower--;
	if (data->swap)
	{
		sa(a);
		data->swap = 0;
		data->lower--;
	}
}

void	add_more(t_stats *data, t_node **a)
{
	rra(a);
	data->bottom--;
	data->lower--;
	if (data->bottom)
		try_more(data, a);
	else
		data->bottom_stack = NULL;
}
