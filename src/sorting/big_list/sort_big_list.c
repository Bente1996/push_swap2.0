/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   sort_big_list.c                                         :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/08 17:40:38 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/08 17:40:40 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_big_list(t_node **a, t_node **b, int all, int size)
{
	int	sorted;
	int	half;

	half = all / 2;
	sorted = half - size;
	organise_b(a, b, half, size);
	organise_a(a, b, all, half + size);
	if (all % 2)
	{
		sort_unorganised(a, b, all, half - size + 1);
		sorted++;
	}
	else
		sort_unorganised(a, b, all, half - size);
	while (sorted--)
	{
		pa(a, b);
		ra(a);
	}
	sort_half(a, b, half + size, size);
	sort_half(a, b, half, half);
}
