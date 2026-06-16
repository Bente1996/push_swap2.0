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

void	sort_unorganised(t_node **a, t_node **b, int half, int count) // andersom
{
	t_stats	data;
	int		group;

	data = init_stats(a, b, half);
	while (count)
	{
		group = 0;
		group = is_group((*a)->n_index, data.lower, data.bottom);
		if (group)
		{
			sort_bottom_stack(&data, a, b, group);
			count--;
		}
		else // rest
			ra(a, 0); // moet dus andersom
	}
}

//void	sort_unorganised(t_node **a, t_node **b, int half, int count) // moet
//																	  // andersom
//{
//	t_stats	data;
//	int		group;
//
//	data = init_stats(a, b, half);
//	while (count)
//	{
//		group = 0;
//		group = is_group((*b)->n_index, data.lower, data.bottom);
//		if (group)
//		{
//			sort_bottom_stack(&data, a, b, group);
//			count--;
//		}
//		else // rest
//			rb(b, data.top); // moet dus andersom
//	}
//}

void	sort_bottom_stack(t_stats *data, t_node **a, t_node **b, int group)
{
	if (group == 1)
		move_to_top_r(data, a, b); // omdraaien, andere func
	else if (group == 2)
		move_to_bottom_r(data, a, b); // omdraaien, andere func
}
