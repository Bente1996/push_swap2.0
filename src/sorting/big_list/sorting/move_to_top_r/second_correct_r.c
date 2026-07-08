/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   try_second.c                                            :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/16 20:00:57 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/16 20:03:48 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

void	second_correct_r(t_stats *data, t_node **b)
{
	sb(b);
	if ((*b)->n_index == (*b)->next->n_index - 1 && data->bottom)
		two_in_order_r(data, b);
	else if (data->bottom_stack->n_index == (*b)->next->n_index - 1)
		add_from_bottom_r(data, b);
	else
		rb(b);
}

void	two_in_order_r(t_stats *data, t_node **b)
{
	data->lower--;
	data->bottom--;
	if (data->bottom_stack->n_index == (*b)->n_index - 1)
	{
		rrb(b);
		data->bottom--;
		data->lower--;
	}
	data->bottom_stack = NULL;
}

void	add_from_bottom_r(t_stats *data, t_node **b)
{
	rrb(b);
	sb(b);
	data->lower--;
	data->bottom--;
	if ((*b)->n_index == (*b)->next->n_index - 1)
	{
		data->lower--;
		data->bottom--;
		data->bottom_stack = NULL;
	}
	else
	{
		rb(b);
		data->bottom_stack = find_bottom(*b);
	}
}
