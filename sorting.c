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
	int	check; // maak check return van operations

	//print_list(*stack_a, 'A');
	//print_list(*stack_b, 'B');
	check = 1;

	if (one_element(stack_a, stack_b, half)) // alleen bij 2 of 3 elementen, maak aparte functies daarvoor
		return ;
	while (!sorted(*stack_a, half, 'A') || !sorted(*stack_b, half, 'B')) // zolang geen goed verdeelde stacks, gaat foutt wanneer b gesorteerd en a niet
	{
		if (one_element(stack_a, stack_b, half)) // toegevoegd bij "1 2 3 4", misschien niet nodig: voeg already_sorted() toe aan begin en ook weer bv bij big_list()
			return ;
		while (check && *stack_a && *stack_b && (*stack_a)->next && (*stack_b)->next) // rr
		{
			check = 0;
			while ((*stack_a)->sorted_index <= half && (*stack_b)->sorted_index > half) // check bij while loop hierboven = afdoende
			{
				rr(stack_a, stack_b);
				check++;
			}
			if ((*stack_a)->next->sorted_index <= half && (*stack_b)->sorted_index > half)
			{
				sa(stack_a);
				rr(stack_a, stack_b);
				check++;
			}
			else if ((*stack_b)->next->sorted_index > half && (*stack_a)->sorted_index <= half)
			{
				sb(stack_b);
				rr(stack_a, stack_b);
				check++;
			}
		} // verlaat wanneer geen rr mogelijkheid
		if (!sorted(*stack_a, half, 'A') && !sorted(*stack_b, half, 'B')) // wanneer beide nog niet gesorteerd zijn
		{
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
			else if (!check && stack_size(*stack_a) > stack_size(*stack_b)) // beide fout, push op basis van stack grootte
			{
				pb(stack_a, stack_b);
				check = 0;
			}
			else if (!check && stack_size(*stack_a) <= stack_size(*stack_b))
			{
				pa(stack_a, stack_b);
				check = 0;
			}
		}
		else if (one_element(stack_a,stack_b, half))
				return ;
		else if (sorted(*stack_a, half, 'A')) // als alleen a gesorteerd: elementen van a in b
		{
			while (!sorted(*stack_b, half, 'B'))
			{				
				if (one_element(stack_a,stack_b, half))
					return ;
				if ((*stack_b)->sorted_index > half)
					rb(stack_b);
				else 
					pa(stack_a, stack_b);
			}
		}
		else
		{
			while (!sorted(*stack_a, half, 'A'))
			{	
				if (one_element(stack_a,stack_b, half))
					return ;
				if ((*stack_a)->sorted_index <= half)
					ra(stack_a);
				else 
					pb(stack_a, stack_b);
			}
		}
	}
}

void	big_list(t_node **stack_a, t_node **stack_b, int half)
{
	int	quarter;
	int	q;
	int	h;

	quarter = half / 2;
	q = quarter;
	h = half;
	printf("Tussenstand:\n");
	printf("Halve:%d\n", half);
	printf("Kwartje:%d\n", quarter);
	print_list(*stack_a, 'A');
	print_list(*stack_b, 'B');
	while (*stack_a) // alles naar b: 25_49 50-99(random) 24_0 (kan misschien optimaler door 0_24 (gelijk pb hierna), 25-74(random)(dit wordt moeilijker), 75_99 (alleen pb dus)
	{
		if ((*stack_a)->sorted_index  == q && ((*stack_a)->sorted_index <= quarter)) // 24->0
		{
			pb(stack_a, stack_b);
			rb(stack_b);
			q--;
		}
		else if ((*stack_a)->sorted_index == h && ((*stack_a)->sorted_index <= half)) // 49 -> 25
		{
			pb(stack_a, stack_b);
			h--;
		}
		else
			ra(stack_a);
	}
	final_list(stack_a, stack_b, half, quarter);
}

void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // 100 nummers 1200 operations
{
	int	higher;

	higher = half + 1;
	while (*stack_b)
	{
		while (half > quarter) // kan in 1 loop: alleen half en kijk naar index voor rrb of niet
		{
			rrb(stack_b);
			pa(stack_a, stack_b);
			half--; // 23 /24
		}
		half++;
		while (half)
		{
			pa(stack_a, stack_b);
			half--;
		}
		while (*stack_b) // kan optimaler
		{
			if ((*stack_b)->sorted_index == higher)
			{
				pa(stack_a, stack_b);
				higher++;
			}
			else
				rb(stack_b);
		}
	}
}

int	random_split(t_node **stack_a, t_node **stack_b, int size)
{
	int	half;
	int	operations;

	half = size / 2;
	while (size > half) // twee random stacks (kan optimaler door al r te doen)
	{
		pb(stack_a, stack_b);
		size--;
	}
	half--; // naar juiste index
	printf("Binnenkomst:\n");
	print_list(*stack_a, 'A');
	print_list(*stack_b, 'B');
	intentional_split(stack_a, stack_b, half);
	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
	operations = count_operations("");
	return (operations);
}
