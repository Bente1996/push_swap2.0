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

void	intentional_split(t_node **stack_a, t_node **stack_b, int half)
{
	int	check;

	check = 1;
	while (!sorted(*stack_a, half, 'A') || !sorted(*stack_b, half, 'B')) // zoveel mogelijk r zolang niet twee goed verdeelde stacks
	{
		while (check) // rr
		{
			check = 0;
			while ((*stack_a)->sorted_index <= half && (*stack_b)->sorted_index > half)
			{
				rr(stack_a, stack_b);
				check++;
			}
			if ((*stack_a)->next && (*stack_b)->next && (*stack_a)->next->sorted_index <= half && (*stack_b)->sorted_index > half)
			{
				ra(stack_a);
				rr(stack_a, stack_b);
				check++;
			}
			else if ((*stack_a)->next && (*stack_b)->next && (*stack_b)->next->sorted_index > half && (*stack_a)->sorted_index <= half)
			{
				rb(stack_b);
				rr(stack_a, stack_b);
				check++;
			}
		} // verlaat wanneer geen rr mogelijkheid
		if ((*stack_a)->sorted_index <= half)  // alleen A goed
		{
			ra(stack_a);
			check++;
		}
		else if ((*stack_b)->sorted_index > half) // alleen B goed
		{
			rb(stack_b);
			check++;
		}
		else if (!check && stack_size(*stack_a) >= stack_size(*stack_b)) // beide fout, push op basis van stack grootte
		{
			pb(stack_a, stack_b);
			check++;
		}
		else if (!check && stack_size(*stack_a) < stack_size(*stack_b))
		{
			pa(stack_a, stack_b);
			check++;
		}
	}	
}

int	random_split(t_node **stack_a, t_node **stack_b, int size)
{
	int	half;
	int	operations;

	half = size / 2;
	while (size > half) // twee random stacks
	{
		pb(stack_a, stack_b);
		size--;
	}
	print_list(*stack_a, 'A');
	print_list(*stack_b, 'B');
	intentional_split(stack_a, stack_b, half);
	operations = count_operations("");
	return (operations);
}
