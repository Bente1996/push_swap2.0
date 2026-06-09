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

static int	is_group(int n_index, int lower, int bottom) // find case
{
	if (n_index == lower || n_index == lower - 1)
		return (1);
	else if ((n_index == lower - 2 || n_index == lower - 3 || n_index == lower - 4) && bottom < 3)
		return (2);
	else
		return (0);
}

void	sort_half(t_node **a, t_node **b, int half, int count)
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
			grow_list(&data, a, b, group);
			count--;
		}
		else // rest
			rb(b, data.top);
	}
}

void	grow_list(t_stats *data, t_node **a, t_node **b, int group)
{
	if (group == 1)
		grow_top(data, a, b);
	else if (group == 2)
		grow_bottom(data, a, b);
}

//void	grow_list(t_node **a, t_node **b, int half, int count) // oud
//{
//	t_stats	data;
//	int	group; // pas namen aan
//
//	data = init_stats(a, b, half);
//	while (count--)
//	{
//		group = find_case((*b)->n_index, data.lower, data.bottom); // is_group?
//		if (group == 1)
//			add_and_lower(&data, a, b);
//		else if (group == 2) // for -2, -3 en -4 (bottom <3)
//			add(&data, a, b);
//		else // rest
//		{
//			rb(b, data.top);
//			count++;
//		}
//	}
//}
