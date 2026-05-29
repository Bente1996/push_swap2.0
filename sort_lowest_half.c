/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   all_to_A.c                                              :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/05/22 17:56:04 by bede-kon            #+#    #+#           */
/*   Updated: 2026/05/22 17:56:10 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	sort_lowest_half(t_node **A, t_node **B, int half) // verander namen (three_quarter -> quarter, A vs B)
{
	t_stats *data;

	data = alloc_stats(A, B, half);
	if (!data)
		return ;
	data->h = half - 1;
	data->tq = 0;
//	print_list(*B, 'B');_
	while (*B)
	{
		if (((*B)->n_index >= data->tq && \
				(*B)->n_index <= data->tq + 2) && (*B)->n_index < data->quarter) // 0-24
			top_to_quarter(data, A, B);
		else if (((*B)->n_index <= data->h && \
				(*B)->n_index >= data->h - 2) && \
				(*B)->n_index >= data->quarter) // 25-49
			quarter_to_half(data, A, B);
		else // was niet de goeie
			rb(B, 0);
		//if ((*A)->n_index == 33)
		//	break ;
	}
	while (data->quarter--)
		rra(A, 0);
}


void	swap_t(t_stats *data, t_node **A, t_node **B)
{
	if (((*B)->n_index != data->bottom_stack->n_index + 1) || data->swap_rot == 2)
		rra(A, 0);
	if (data->swap_rot == 2)
		rra(A, 0);
	pa(A, B, 0);
	ra(A, 0);
	data->bottom_stack = find_bottom(*A);
	if (data->swap_rot == 2)
	{
		if ((*A)->n_index > (*A)->next->n_index)
			sa(A, 0);
		while (data->swap_rot)
		{
			ra(A, 0);
			data->swap_rot--;
			data->tq++;
		}
	}
	else if ((*A)->n_index == data->bottom_stack->n_index + 1)
	{
		ra(A, 0);
		data->tq++;
		data->swap_rot--;
	}
	else
		ra(A, 0);
	data->bottom_stack = find_bottom(*A);
	data->tq++;
}

