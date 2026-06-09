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

void	sort_highest_half(t_node **a, t_node **b, int half)
{
	t_stats	data;

	data = init_stats(a, b, half);
	data.h++;
	while (*a)
	{
		if ((*a)->n_index >= data.tq && (*a)->n_index <= data.tq + 2) //75->99
			tq_to_all(&data, a, b);
		else if ((*a)->n_index >= data.h && (*a)->n_index <= data.h + 2) //50->74
			half_to_tq(&data, a, b);
		else
			ra(a, 0);
	}
}
