/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   sorting.c                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/13 15:30:43 by bede-kon            #+#    #+#           */
/*   Updated: 2026/03/13 17:40:28 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	sort_all(t_node **stack_a, t_node **stack_b, int all)
{
	int	size;

	size = (((all / 2) / 45) - 1) * 45;
	if (size > 180)
		size = 180;
	if (size < 45)
		size = 45;
	if (stack_size(*stack_a) >=  150)
		sort_small(stack_a, stack_b, all, size); // GL+GL(organisex2): 150
	else
		random_split(stack_a, stack_b, all); // BL+GL+group: 405 vOOr grow_list, 662 NA, 635 met group
}

void	sort_small(t_node **stack_a, t_node **stack_b, int all, int size) // GL x2
{
	int 	sorted;
	int	half;

	half = all / 2;
	sorted = half - size;
    	organise_B_small(stack_a, stack_b, half, size);
	organise_A_small(stack_a, stack_b, all, half + size); // 70 in A, bovenste = 499, toeval
	if (all != half * 2)
	{
		grow_list(stack_b, stack_a, all, half - size + 1);
		sorted++;
	}
	else
		grow_list(stack_b, stack_a, all, half - size);
	while (sorted--)
	{
		pa(stack_a, stack_b, 0);
		if (*stack_a)
			ra(stack_a, 0);
	}
	grow_list(stack_a, stack_b, half + size, size);
	grow_list(stack_a, stack_b, half, half);
}
