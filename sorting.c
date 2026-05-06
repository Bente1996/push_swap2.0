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

void	sort_all(t_node **stack_a, t_node **stack_b, int half)
{
	int	all;

	all = stack_size(*stack_a);	
	if (all > 359)
		sort_big(stack_a, stack_b, all, half);
//	else
//		small_sort(stack_a, stack_b);
}

void	sort_small(t_node **stack_a, t_node **stack_b, int all, int half)
{
	int 	sorted;
	int	size = 135;

	sorted = half - size;
	organise_B(stack_a, stack_b, half); // organise afhangende van grootte, even/oneven getal
	if (all != half * 2)
	{
		organise_A(stack_a, stack_b, half + size, half + 1);
		grow_list(stack_b, stack_a, half * 2 + 1, half - size - 1); // test met andere getallen, totaal 430+
		sorted++;
	}
	else
	{
		organise_A(stack_a, stack_b, half + size, half);
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

void	sort_big(t_node **stack_a, t_node **stack_b, int all, int half)
{
	int 	sorted;

	sorted = half - 180;
	organise_B(stack_a, stack_b, half); // organise afhangende van grootte, even/oneven getal
	if (all != half * 2)
	{
		organise_A(stack_a, stack_b, half + 180, half + 1);
		grow_list(stack_b, stack_a, half * 2 + 1, half - 179); // test met andere getallen, totaal 430+
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
