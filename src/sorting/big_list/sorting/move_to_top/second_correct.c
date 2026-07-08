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

void	second_correct(t_stats *data, t_node **a)
{
	sa(a);
	if ((*a)->n_index == (*a)->next->n_index - 1 && data->bottom)
		two_in_order(data, a);
	else if (data->bottom_stack->n_index == (*a)->next->n_index - 1)
		add_from_bottom(data, a);
	else
		ra(a);
}

void	two_in_order(t_stats *data, t_node **a)
{
	data->lower--;
	data->bottom--;
	if (data->bottom_stack->n_index == (*a)->n_index - 1)
	{
		rra(a);
		data->bottom--;
		data->lower--;
	}
	data->bottom_stack = NULL;
}

void	add_from_bottom(t_stats *data, t_node **a)
{
	rra(a);
	sa(a);
	data->lower--;
	data->bottom--;
	if ((*a)->n_index == (*a)->next->n_index - 1)
	{
		data->lower--;
		data->bottom--;
		data->bottom_stack = NULL;
	}
	else
	{
		ra(a);
		data->bottom_stack = find_bottom(*a);
	}
}
