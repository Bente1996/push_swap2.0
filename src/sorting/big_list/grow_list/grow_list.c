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

void	grow_list(t_node **a, t_node **b, int half, int count) // werkt normaal
{
	t_stats	data;
	int	n; // pas namen aan

	data = init_stats(a, b, half);
	while (count--)
	{
		n = find_case((*b)->n_index, data.lower, data.bottom); // goed
		if (n == 1)
			add_and_lower(&data, a, b);
		else if (n == 2) // for -2, -3 en -4 (bottom <3)
			add(&data, a, b);
		else // rest
		{
			rb(b, data.top);
			count++;
		}
	}
}
