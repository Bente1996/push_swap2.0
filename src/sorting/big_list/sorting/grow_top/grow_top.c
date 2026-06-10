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

void	grow_top(t_stats *data, t_node **a, t_node **b) // add_and_lower
{
	pa(a, b, data->top);
	if ((*a)->n_index == data->lower - 1) // lower nog niet gevonden
		data->swap++;
	else
		add_one(data, a);           // lower wel gevonden
	if (data->bottom && data->bottom_stack->n_index == data->lower)
		add_more(data, a);
}

void	add_one(t_stats *data, t_node **a) //handle bottom
{
	data->lower--;
	if (data->swap)
	{
		sa(a, data->top);
		data->swap = 0;
		data->lower--;
	}
}

void	add_more(t_stats *data, t_node **a)
{
	rra(a, data->top);
	data->bottom--;
	data->lower--;
	if (data->bottom)
		try_more(data, a); // get more bottom if bottom
	else
		data->bottom_stack = NULL;
}

void	try_more(t_stats *data, t_node **a)
{
	if ((*a)->n_index == data->lower + 1) // eerste was goed
	{
		data->bottom_stack = find_bottom(*a);
		if (!add_second(data, a) && data->bottom == 2) // check tweede
				try_third(data, a); // tweede mag niet, probeer derde
	}
	else // eerste was niet goed dus probeer tweede
		 try_second(data, a);
}

void	try_second(t_stats *data, t_node **A)
{
	rra(A, data->top);
	if (data->bottom == 2)
		data->bottom_stack = find_bottom(*A);
	else
		data->bottom_stack = (*A)->next;
	if ((*A)->n_index == (*A)->next->next->n_index - 1) // als tweede goed is
	{
		sa(A, data->top);
		if ((*A)->n_index == (*A)->next->n_index - 1 && data->bottom) // twee op juiste plek
			check_third(data, A);
		else if (data->bottom_stack->n_index == (*A)->next->n_index - 1) // niet twee juiste volgorde
			add_third(data, A);
		else // tweede was niet goed
		     ra(A, data->top);
	}
	else // tweede was niet goed, dus moet derde wel zijn
		 get_third(data, A);
}
