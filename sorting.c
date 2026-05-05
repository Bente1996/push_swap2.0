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
	int unsorted;

	unsorted = half - 180;
	organise_B(stack_a, stack_b, half); // organise afhangende van grootte, even/oneven getal
	organise_A(stack_a, stack_b, half + 180);
	grow_list(stack_b, stack_a, half * 2, half - 180); // test met andere getallen, totaal 430+
	while (unsorted--)
	{
		pa(stack_a, stack_b);
		if (*stack_a)
			ra(stack_a);
	}
	grow_list(stack_a, stack_b, half + 180, 180);
	grow_list(stack_a, stack_b, half, half);
}

t_node	*sort_indices(t_node **list)
{
	t_node	*head;
	t_node	*tmp;

	head = *list;
	tmp = *list;
	while (tmp)
	{
		while (*list)
		{
			if (tmp->value > (*list)->value)
				tmp->sorted_index += 1;
			if (!(*list)->next)
				break ;
			*list = (*list)->next;
		}
		*list = head;	
		tmp = tmp->next;
	}
	return (head);
}


