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


void	move_to_bottom(t_stats *data, t_node **a, t_node **b) // add
{
	if (!data->bottom || data->bottom_stack->n_index < (*b)->n_index)
	{
		pa(a, b);
		ra(a);
		data->bottom_stack = find_bottom(*a);
	}
	else
	{
		pa(a, b);
		ra(a);
	}
	data->bottom++;
}

void	move_to_bottom_r(t_stats *data, t_node **a, t_node **b) // add
{
	if (!data->bottom || data->bottom_stack->n_index < (*a)->n_index)
	{
		pb(a, b);
		rb(b);
		data->bottom_stack = find_bottom(*b);
	}
	else
	{
		pb(a, b);
		rb(b);
	}
	data->bottom++;
}
