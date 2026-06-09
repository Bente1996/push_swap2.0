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

void	add_new_lower(t_stats *data, t_node **A) // add_two_lower
{
	rra(A, data->top);
	data->bottom--;
	data->lower--;
	if (data->bottom)
		more_bottom(data, A);
	else
		data->bottom_stack = NULL;
}

void	more_bottom(t_stats *data, t_node **A) // add_three_lower,etc.
{
	if ((*A)->n_index == (*A)->next->n_index - 1) // eerste was goed
	{
		data->bottom_stack = find_bottom(*A);
		if (!add_second(data, A) && data->bottom == 2) // check tweede
				try_three(data, A); // tweede mag niet, probeer derde
	}
	else // eerste was niet goed dus probeer tweede
		 try_two(data, A);
}

void	try_three(t_stats *data, t_node **A)
{
	data->bottom_stack = check_bottom(*A);
	if (data->bottom_stack->n_index == (*A)->n_index - 1)
	{
		rra(A, data->top);
		rra(A, data->top);
		sa(A, data->top);
		data->lower--;
		data->bottom--;
	}
	if ((*A)->n_index != (*A)->next->n_index - 1)
	{
		ra(A, data->top);
		data->bottom_stack = find_bottom(*A);
	}
	else
	{
		data->bottom--;
		data->bottom_stack = NULL;
		data->lower--;
	}
}

void	try_two(t_stats *data, t_node **A)
{
	rra(A, data->top);
	if (data->bottom == 2)
		data->bottom_stack = find_bottom(*A);
	else
		data->bottom_stack = (*A)->next;
	if ((*A)->n_index == (*A)->next->next->n_index - 1) // als tweede goed is
	{
		sa(A, data->top);
		if ((*A)->n_index == (*A)->next->n_index - 1) // twee op juiste plek
			check_third(data, A);
		else if (data->bottom_stack->n_index == (*A)->next->n_index - 1) // niet twee juiste volgorde
			get_second(data, A);
		else // tweede was niet goed
		     ra(A, data->top);
	}
	else // tweede was niet goed, dus moet derde wel zijn
		 get_third(data, A);
}
