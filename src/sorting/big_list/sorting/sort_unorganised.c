/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   sort_unorganised.c                                      :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/09 19:19:43 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/09 19:44:57 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_group(int n_index, int lower, int bottom) // find case
{
	if (n_index == lower || n_index == lower - 1)
		return (1);
	else if ((n_index == lower - 2 || n_index == lower - 3 || n_index == lower - 4) && bottom < 3)
		return (2);
	else
		return (0);
}

void	sort_unorganised(t_node **a, t_node **b, int half, int count) // moet
																	  // andersom
{
	t_stats	data;
	int	group;

	data = init_stats(a, b, half);
	while (count)
	{
		group = 0;
		group = is_group((*b)->n_index, data.lower, data.bottom);
		if (group)
		{
			sort_bottom_stack(&data, a, b, group);
			count--;
		}
		else // rest
			rb(b, data.top); // moet dus andersom
	}
}

void	sort_bottom_stack(t_stats *data, t_node **a, t_node **b, int group) // omdraaien
{
	if (group == 1)
		grow_top(data, a, b); // omdraaien, andere func
	else if (group == 2)
		grow_bottom(data, a, b); // omdraaien, andere func
}
