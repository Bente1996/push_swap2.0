/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   lowering_utils.c                                        :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/08 17:41:40 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/08 17:48:47 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>



void	funk(t_stats *data, t_node **A)
{
	data->bottom--;
	data->lower--;
	if (data->bottom_stack->n_index == (*A)->n_index - 1)
	{
		rra(A, data->top);
		data->bottom--;
		data->lower--;
		data->bottom_stack = NULL;
	}
}


void	fonk(t_stats *data, t_node **A)
{
	rra(A, data->top);
	sa(A, data->top);
	data->lower--;
	data->bottom--;
	if ((*A)->n_index == (*A)->next->n_index - 1)
	{
		data->bottom--;
		data->lower--;
		data->bottom_stack = NULL;
	}
	else
	{
		ra(A, data->top);
		data->bottom_stack = find_bottom(*A);
	}
}

