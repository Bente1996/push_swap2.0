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

void	move_to_top_r(t_stats *data, t_node **a, t_node **b) // add_and_lower
{
	pb(a, b);
	if ((*b)->n_index == data->lower - 1) // lower nog niet gevonden
		data->swap++;
	else
		add_one_r(data, b);           // lower wel gevonden
	if (data->bottom && data->bottom_stack->n_index == data->lower)
		add_more_r(data, b);
}

void	add_one_r(t_stats *data, t_node **b) //handle bottom
{
	data->lower--;
	if (data->swap)
	{
		sb(b);
		data->swap = 0;
		data->lower--;
	}
}

void	add_more_r(t_stats *data, t_node **b)
{
	rrb(b); // 1 (van 3?) naar boven
	data->bottom--;
	data->lower--;
	if (data->bottom)
		try_more_r(data, b); // get more bottom if bottom (bottom == 1-2)
	else
		data->bottom_stack = NULL;
}
