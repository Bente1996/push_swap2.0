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

void	sort_lowest_half(t_node **A, t_node **B, int half) // verander namen (three_quarter -> quarter, A vs B)
{
	t_stats *data;

	data = alloc_stats(A, B, half);
	if (!data)
		return ;
	data->h = half - 1;
	data->tq = 0;
	while (*B)
	{
		if (((*B)->n_index >= data->tq 
			&& (*B)->n_index <= data->tq + 2) 
			&& (*B)->n_index < data->quarter) // 0-24
			top_to_quarter(data, A, B);
		else if (((*B)->n_index <= data->h && \
				(*B)->n_index >= data->h - 2) && \
				(*B)->n_index >= data->quarter) // 25-49
			quarter_to_half(data, A, B);
		else // was niet de goeie
			rb(B, 0);
		// if ((*A)->n_index == 33)
		// 	break ;
	}
	while (data->quarter--)
		rra(A, 0);
}
