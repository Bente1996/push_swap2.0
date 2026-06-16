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

void	sort_lowest_half(t_node **a, t_node **b, int half)
{
	t_stats data;

	data = init_stats(half);
	while (*b)
	{
		if ((*b)->n_index >= data.q 
			&& (*b)->n_index <= data.q + 2
			&& (*b)->n_index < data.quarter) // 0-24
			top_to_quarter(&data, a, b);
		else if ((*b)->n_index <= data.h && (*b)->n_index >= data.h - 2) // 25-49
			quarter_to_half(&data, a, b);
		else
			rb(b);
	}
	while (data.quarter--)
		rra(a);
}
