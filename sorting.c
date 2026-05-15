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

void	big_lists(t_node **stack_a, t_node **stack_b, int all) // 2x big list, voeg randomsplitshit toe, maar pas groep aan naar 2x 3
{
	int	half = all / 2;

	while (stack_size(*stack_b) < half)
	{
		if ((*stack_a)->sorted_index < half)
				pb(stack_a, stack_b);
		else
			ra(stack_a, 0);
	}
	big_list(stack_a, stack_b, half);
	if (all % 2)
		sorted_to_A(stack_a, stack_b, half + 1, half / 2);
	else
		sorted_to_A(stack_a, stack_b, half, half / 2);
	big_list_two(stack_b, stack_a, half);
}

void	bl_gl(t_node **stack_a, t_node **stack_b, int all, int size)
{
	int	half;

	half = all / 2;  

	organise_B_small(stack_a, stack_b, half, size);
	big_list(stack_a, stack_b, half);
	sorted_to_A(stack_a, stack_b, half, half / 2);
	grow_list(stack_a, stack_b, half, half);
}

void	sort_all(t_node **stack_a, t_node **stack_b, int all)
{
	int	size;

//	size = 180;
//	size = 135;
//	size = 90;
//	size = 45;
	size = (((all / 2) / 45) - 1) * 45;
	if (size > 180)
		size = 180;
	if (size < 45)
		size = 45;
//	big_lists(stack_a, stack_b, all); // BL+BL: 395 vOOr big_list_two, 641 NA, check oneven en group 2x3? = 635!
//	bl_gl(stack_a, stack_b, all, size); // BL+GL(organisex1): 722 NA grow_list
	if (stack_size(*stack_a) >=  150)
		sort_small(stack_a, stack_b, all, size); // GL+GL(organisex2): 150
	else
		random_split(stack_a, stack_b, all); // BL+GL+group: 405 vOOr grow_list, 662 NA, 635 met group
//	print_list(*stack_a, 'A');
//	print_list(*stack_b, 'B');
//	printf("%d %d\n", stack_size(*stack_a), stack_size(*stack_b));
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
