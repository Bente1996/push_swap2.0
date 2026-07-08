/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   grow_list.c                                             :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/08 17:34:09 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/08 17:48:59 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_group(int n_index, int lower, int bottom)
{
	if (n_index == lower || n_index == lower - 1)
		return (1);
	else if (bottom < 3
		&& (n_index == lower - 2
			|| n_index == lower - 3
			|| n_index == lower - 4))
		return (2);
	else
		return (0);
}

void	sort_half(t_node **a, t_node **b, int half, int count)
{
	t_stats	data;
	int		group;

	data = init_stats(half);
	while (count)
	{
		group = is_group((*b)->n_index, data.lower, data.bottom);
		if (group)
		{
			grow_list(&data, a, b, group);
			count--;
		}
		else
			rb(b);
	}
}

void	grow_list(t_stats *data, t_node **a, t_node **b, int group)
{
	if (group == 1)
		move_to_top(data, a, b);
	else if (group == 2)
		move_to_bottom(data, a, b);
}
