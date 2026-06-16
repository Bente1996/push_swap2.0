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

void	try_more(t_stats *data, t_node **a)
{
	if ((*a)->n_index == data->lower + 1) // eerste was goed
	{
		data->bottom_stack = find_bottom(*a);
		if (!add_second(data, a) && data->bottom == 2) // check tweede EN derde
			try_third(data, a); // tweede mag niet, probeer derde
	}
	else // eerste was niet goed dus probeer tweede
		try_second(data, a);
}

bool	add_second(t_stats *data, t_node **a)
{
	if (data->bottom_stack->n_index == (*a)->n_index - 1) // tweede mag ook
	{
		rra(a, data->top);
		data->bottom--;
		data->lower--;
		if (data->bottom)
			data->bottom_stack = find_bottom(*a);
		else
			data->bottom_stack = NULL;
		if (data->bottom && data->bottom_stack->n_index == (*a)->n_index - 1)
		{
			rra(a, data->top);
			data->lower--;
			data->bottom_stack = NULL;
			data->bottom--;
		}
		return (true);
	}
	else
		return (false);
}

void	try_third(t_stats *data, t_node **a)
{
	data->bottom_stack = check_bottom(*a);
	if (data->bottom_stack->n_index == (*a)->n_index - 1)
	{
		rra(a, data->top);
		rra(a, data->top);
		sa(a, data->top);
		data->lower--;
		data->bottom--;
	}
	if ((*a)->n_index != (*a)->next->n_index - 1)
	{
		ra(a, data->top);
		data->bottom_stack = find_bottom(*a);
	}
	else
	{
		data->bottom--;
		data->bottom_stack = NULL;
		data->lower--;
	}
}

void	try_second(t_stats *data, t_node **a)
{
	rra(a, data->top);
	if (data->bottom == 2)
		data->bottom_stack = find_bottom(*a);
	else
		data->bottom_stack = (*a)->next;
	if ((*a)->n_index == (*a)->next->next->n_index - 1) // als tweede goed is
		second_correct(data, a);
	else // tweede was niet goed, dus moet derde wel zijn
		get_third(data, a);
}
