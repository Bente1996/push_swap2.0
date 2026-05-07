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
	size = (((all / 2) / 45) - 1) * 45;
	if (!size)
		size = 0; // klopt niet
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
	printf("half: %d\n", half);
	printf("size: %d\n", size);
    organise_B_small(stack_a, stack_b, half, size);
	if (all != half * 2)
	{
		organise_A_small(stack_a, stack_b, all, half + size); // deze goed maken voor oneven
		  						   // !!!!! :D
		grow_list(stack_b, stack_a, half * 2 + 1, half - size + 1);
		sorted++;
	}
	else
	{
		organise_A_small(stack_a, stack_b, all, half + size);
		grow_list(stack_b, stack_a, half * 2, half - size);
	}
	while (sorted--)
	{
		pa(stack_a, stack_b);
		if (*stack_a)
			ra(stack_a);
	}
	grow_list(stack_a, stack_b, half + size, size);
	grow_list(stack_a, stack_b, half, half);
}

void	sort_big(t_node **stack_a, t_node **stack_b, int all)
{
	int 	sorted;
	int	half = all / 2;

	sorted = half - 180; // - size
	organise_B(stack_a, stack_b, half);
	if (all != half * 2)
	{
		organise_A(stack_a, stack_b, half + 180, half + 1);
		grow_list(stack_b, stack_a, half * 2 + 1, half - 179);
		sorted++;
	}
	else
	{
		organise_A(stack_a, stack_b, half + 180, half);
		grow_list(stack_b, stack_a, half * 2, half - 180);
	}
	while (sorted--)
	{
		pa(stack_a, stack_b);
		if (*stack_a)
			ra(stack_a);
	}
	grow_list(stack_a, stack_b, half + 180, 180);
	grow_list(stack_a, stack_b, half, half);
}
