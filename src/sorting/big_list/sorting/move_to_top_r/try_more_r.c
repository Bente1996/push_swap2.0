/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   lowering.c                                              :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/08 17:41:06 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/08 17:48:51 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

void	try_more_r(t_stats *data, t_node **b)
{
	if ((*b)->n_index == data->lower + 1) // eerste was goed
	{
		data->bottom_stack = find_bottom(*b);
		if (!add_second_r(data, b) && data->bottom == 2) // check tweede EN derde
			try_third_r(data, b); // tweede mag niet, probeer derde
	}
	else // eerste was niet goed dus probeer tweede
		try_second_r(data, b);
}

bool	add_second_r(t_stats *data, t_node **b)
{
	if (data->bottom_stack->n_index == (*b)->n_index - 1) // tweede mag ook
	{
		rrb(b);
		data->bottom--;
		data->lower--;
		if (data->bottom)
			data->bottom_stack = find_bottom(*b);
		else
			data->bottom_stack = NULL;
		if (data->bottom && data->bottom_stack->n_index == (*b)->n_index - 1)
		{
			rrb(b);
			data->lower--;
			data->bottom_stack = NULL;
			data->bottom--;
		}
		return (true);
	}
	else
		return (false);
}

void	try_third_r(t_stats *data, t_node **b)
{
	data->bottom_stack = check_bottom(*b);
	if (data->bottom_stack->n_index == (*b)->n_index - 1)
	{
		rrb(b);
		rrb(b);
		sb(b);
		data->lower--;
		data->bottom--;
	}
	if ((*b)->n_index != (*b)->next->n_index - 1)
	{
		rb(b);
		data->bottom_stack = find_bottom(*b);
	}
	else
	{
		data->bottom--;
		data->bottom_stack = NULL;
		data->lower--;
	}
}

void	try_second_r(t_stats *data, t_node **b)
{
	rrb(b);
	if (data->bottom == 2)
		data->bottom_stack = find_bottom(*b);
	else
		data->bottom_stack = (*b)->next;
	if ((*b)->n_index == (*b)->next->next->n_index - 1) // als tweede goed is
		second_correct_r(data, b);
	else // tweede was niet goed, dus moet derde wel zijn
		get_third_r(data, b);
}
