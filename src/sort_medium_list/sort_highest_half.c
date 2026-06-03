/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   all_to_B.c                                              :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/05/22 17:44:42 by bede-kon            #+#    #+#           */
/*   Updated: 2026/05/22 18:05:24 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_highest_half(t_node **A, t_node **B, int half)
{
	t_stats *data;

	data = alloc_stats(A, B, half);
	if (!data)
		return ;
	data->h++;
	while (*A)
	{
		if ((*A)->n_index >= data->tq && (*A)->n_index <= data->tq + 2) // 75->99
			tq_to_all(data, A, B);
		else if ((*A)->n_index >= data->h && (*A)->n_index <= data->h + 2) // 50->74	
			half_to_tq(data, A, B);
		else
			ra(A, 0);
	}
}
