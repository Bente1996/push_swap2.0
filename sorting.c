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

//void	big_list(t_node **stack_a, t_node **stack_b, int half) // werkt met + 1
//{
//	int	whole;
//	int	quarter;
//	int	three_quarter;
//	int	t_q;
//	int	h;
//	int	swap;
//	int	swap_rot;
//
//	whole = half * 2;
//	quarter = half / 2;
//	three_quarter = whole - quarter;
//	t_q = three_quarter + 1;
//	h = half + 1;
//	swap = 0;
//	swap_rot = 0;
//	printf("Tussenstand:\n");
//	printf("Halve:%d\n", half); // 49
//	printf("Kwartje:%d\n", quarter); //24
//	printf("TQ:%d\n", three_quarter); //74
//	print_list(*stack_a, 'A');
//	print_list(*stack_b, 'B');	
//	while (*stack_a) // alles naar b: 73_50 0-49(random) 74_99
//	{
//		printf("t_q: %d\n", t_q);
//		printf("h: %d\n", h);
//		if (((*stack_a)->sorted_index  == t_q || ((*stack_a)->sorted_index == t_q + 1)) && (*stack_a)->sorted_index > three_quarter) // 75->99
//		{
//			if ((*stack_a)->sorted_index == t_q + 1)
//			{
//				pb(stack_a, stack_b);
//				swap_rot++;
//				t_q--; // blijf zoeken naar dezelfde
//			}
//			else if (swap_rot)
//			{
//				rrb(stack_b); // haal naar boven
//				pb(stack_a, stack_b);
//				rb(stack_b);
//				swap_rot = 0;
//				t_q++;
//			}
//			else
//				pb(stack_a, stack_b);
//			rb(stack_b);
//			t_q++;
//		}
//		else if (((*stack_a)->sorted_index == h || ((*stack_a)->sorted_index == h + 1)) && (*stack_a)->sorted_index <= three_quarter) // 50->74
//		{
//			if ((*stack_a)->sorted_index == h + 1)
//			{
//				pb(stack_a, stack_b);
//				swap++;
//				h--; // h + 1 is al gevonden dus zal niet hierna gevonden worden
//			}
//			else if (swap)
//			{
//				pb(stack_a, stack_b);
//				sb(stack_b);
//				swap = 0;
//				h++;
//			}
//			else
//				pb(stack_a, stack_b);
//			h++;
//		}
//		else
//			ra(stack_a);
//	}
//	final_list(stack_a, stack_b, half, quarter);
//}


int	random_split(t_node **stack_a, t_node **stack_b, int size)
{
	int	half;
	int	h;
	int	operations;

	half = size / 2;
	h = half;
	//while (size > half) // twee random stacks (kan optimaler door al r te doen)
	//{
	//	pb(stack_a, stack_b);
	//	size--;
	//}
	printf("%d\n", half);
	while (h)
	{
		if ((*stack_a)->sorted_index < half) // voeg s toe: NEE geprobeerd
		{
			pb(stack_a, stack_b);
			h--;
		}
		else
			ra(stack_a);
	}
	half--; // naar juiste index
	printf("Binnenkomst:\n");
	print_list(*stack_a, 'A');
	print_list(*stack_b, 'B');
//	intentional_split(stack_a, stack_b, half);
	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
	operations = count_operations("");
	return (operations);
}
