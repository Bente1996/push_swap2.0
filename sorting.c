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

//	size = 180;
//	size = 135;
//	size = 90;
//	size = 45;
	size = (((all / 2) / 45) - 1) * 45;
//	if (size <= 0)
//		size = 0; // klopt niet
	printf("size: %d\n", size);
	if (all > 359)
	{
		sort_small(stack_a, stack_b, all, size); // uniform maken
	}
	else // 270
		sort_small(stack_a, stack_b, all, size);
}

void	sort_small(t_node **stack_a, t_node **stack_b, int all, int size)
{
	int 	sorted;
	int	half;

    	half = all / 2;
	sorted = half - size;
    	organise_B_small(stack_a, stack_b, half, size);
	//big_list(stack_a, stack_b, half);              // 100 werkt 99 niet
	organise_A_small(stack_a, stack_b, all, half + size);
	if (all != half * 2)
	{
		grow_list(stack_b, stack_a, all, half - size + 1);
		sorted++;
	}
	else
		grow_list(stack_b, stack_a, all, half - size);
	while (sorted--)
	{
		pa(stack_a, stack_b);
		if (*stack_a)
			ra(stack_a);
	}
	grow_list(stack_a, stack_b, half + size, size);
//	sorted_to_A(stack_a, stack_b, half, half / 2);
	grow_list(stack_a, stack_b, half, half);
}
