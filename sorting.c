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
			while ((*stack_a)->sorted_index >= half && (*stack_b)->sorted_index < half) // check bij while loop hierboven = afdoende
			{
				rr(stack_a, stack_b);
				check++;
			}
			if ((*stack_a)->next->sorted_index >= half && (*stack_b)->sorted_index < half)
			{
				sa(stack_a);
				rr(stack_a, stack_b);
				check++;
			}
			else if ((*stack_b)->next->sorted_index < half && (*stack_a)->sorted_index >= half)
			{
				sb(stack_b);
				rr(stack_a, stack_b);
				check++;
			}
		} // verlaat wanneer geen rr mogelijkheid
		if (!sorted(*stack_a, half, 'A') && !sorted(*stack_b, half, 'B')) // wanneer beide nog niet gesorteerd zijn
		{
			if ((*stack_a)->sorted_index >= half)  // alleen A goed 
			{
				ra(stack_a);
				check++;
			}
			else if ((*stack_b)->sorted_index < half) // alleen B goed
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
				if ((*stack_b)->sorted_index < half)
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
				if ((*stack_a)->sorted_index >= half)
					ra(stack_a);
				else 
					pb(stack_a, stack_b);
			}
		}
	}
}

void	big_list(t_node **stack_a, t_node **stack_b, int half)
{
	int	whole;
	int	quarter;
	int	three_quarter;
	int	t_q;
	int	h;
	int	swap;
	int	swap_rot;

	whole = half * 2;
	quarter = half / 2;
	three_quarter = whole - quarter;
	t_q = three_quarter + 1;
	h = half + 1;
	swap = 0;
	swap_rot = 0;
	printf("Tussenstand:\n");
	printf("Halve:%d\n", half); // 49
	printf("Kwartje:%d\n", quarter); //24
	printf("TQ:%d\n", three_quarter); //74
	print_list(*stack_a, 'A');
	print_list(*stack_b, 'B');	
	while (*stack_a) // alles naar b: 73_50 0-49(random) 74_99
	{
		printf("t_q: %d\n", t_q);
		printf("h: %d\n", h);
		if (((*stack_a)->sorted_index  == t_q || ((*stack_a)->sorted_index == t_q + 1)) && (*stack_a)->sorted_index > three_quarter) // 75->99
		{
			if ((*stack_a)->sorted_index == t_q + 1)
			{
				pb(stack_a, stack_b);
				swap_rot++;
				t_q--; // blijf zoeken naar dezelfde
			}
			else if (swap_rot)
			{
				rrb(stack_b); // haal naar boven
				pb(stack_a, stack_b);
				rb(stack_b);
				swap_rot = 0;
				t_q++;
			}
			else
				pb(stack_a, stack_b);
			rb(stack_b);
			t_q++;
		}
		else if (((*stack_a)->sorted_index == h || ((*stack_a)->sorted_index == h + 1)) && (*stack_a)->sorted_index <= three_quarter) // 50->74
		{
			if ((*stack_a)->sorted_index == h + 1)
			{
				pb(stack_a, stack_b);
				swap++;
				h--; // h + 1 is al gevonden dus zal niet hierna gevonden worden
			}
			else if (swap)
			{
				pb(stack_a, stack_b);
				sb(stack_b);
				swap = 0;
				h++;
			}
			else
				pb(stack_a, stack_b);
			h++;
		}
		else
			ra(stack_a);
	}
	final_list(stack_a, stack_b, half, quarter);
}

void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // 100 nummers 1200 operations
{ 
	int	lower; 
	int	swap;
	int	bottom;
	t_node	*bottom_stack = NULL;

	lower = half;
	swap = 0;
	bottom = 0;

	while (half > quarter) // kan in 1 loop: alleen half en kijk naar index voor rrb of niet, quarter = 24 lower = 49
	{
		rrb(stack_b);
		pa(stack_a, stack_b);
		half--;
	}
	half++; // kan dit  optimaler? maakt wss heel weinig uit
	while (half)
	{
		pa(stack_a, stack_b);
		half--;
	}
	while (*stack_b) // kan optimaler
	{
		if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1) // als 48 of 49 gevonden
		{
			if ((*stack_b)->sorted_index == lower - 1) // verkeerde bovenaan
			{
				pa(stack_a, stack_b);
				swap++;
				lower++; // houdt originele getal aan
			}
			else if (swap) // goede gevonden, zet eronder, lijst klopt, als bottom: zet boven
			{
				pa(stack_a, stack_b);
				sa(stack_a);
				swap = 0;
				lower--; // 49 -> 47
			}
			else // lijst klopt, gewoon 1 erbij, check of bottom aansluit
				pa(stack_a, stack_b);
			lower--;
			if (bottom && (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1))
			{
				while (bottom)
				{
					rra(stack_a);
					lower--;
					bottom--;
				}
				if ((*stack_a)->sorted_index > (*stack_a)->next->sorted_index) // 49, 48, 46 ,47: sa
					sa(stack_a);
				bottom_stack = NULL;
				bottom = 0;
			}
		}
		else if (((*stack_b)->sorted_index == (*stack_a)->sorted_index - 2 || (*stack_b)->sorted_index == (*stack_a)->sorted_index - 3) && bottom < 2)
		{
			pa(stack_a, stack_b);
			if (!bottom || (*stack_a)->sorted_index > bottom_stack->sorted_index) // bottom_stack == grootste index
				bottom_stack = find_bottom(*stack_a);
			ra(stack_a); // zet onderaan A tot ie boven kan aansluiten
			bottom++;
		}
		else// niks interessants gevonden
		{
			printf("LOWER: %d\n", lower);
			printf("stack_b: %d\n", (*stack_b)->sorted_index);
			rb(stack_b);
		}
		if (bottom && (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1))
		{
			while (bottom)
			{
				rra(stack_a);
				lower--;
				bottom--;
			}
			if ((*stack_a)->sorted_index > (*stack_a)->next->sorted_index) // 49, 48, 46 ,47: sa
				sa(stack_a);
			bottom_stack = NULL;
			bottom = 0;
		}
	}
	//while (*stack_b && half)
	//{
	//	while (half > quarter) // kan in 1 loop: alleen half en kijk naar index voor rrb of niet, quarter = 24 lower = 49
	//	{
	//		rrb(stack_b);
	//		pa(stack_a, stack_b);
	//		half--;
	//	}
	//	half++; // kan dit  optimaler? maakt wss heel weinig uit
	//	while (half)
	//	{
	//		pa(stack_a, stack_b);
	//		half--;
	//	}
	//	while (*stack_b) // kan optimaler
	//	{
	//		if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1)
	//		{
	//			if ((*stack_b)->sorted_index == lower - 1) // verkeerde bovenaan
	//			{
	//				pa(stack_a, stack_b);
	//				swap++;
	//				lower++;
	//			}
	//			else if (swap) // goede gevonden, zet eronder, lijst klopt, als bottom: zet boven
	//			{
	//				pa(stack_a, stack_b);
	//				sa(stack_a);
	//				swap = 0;
	//				if (bottom)
	//				{
	//					rra(stack_a);
	//					bottom_stack = NULL;
	//					bottom = 0;
	//					lower--;
	//				}
	//				lower--;
	//			}
	//			else // lijst klopt, gewoon 1 erbij, check of bottom aansluit
	//			{
	//				pa(stack_a, stack_b);
	//				if (bottom && bottom_stack->sorted_index == lower - 1)
	//				{
	//					rra(stack_a);
	//					bottom_stack = NULL;
	//					bottom = 0;
	//					lower--;
	//				}
	//			}
	//			lower--;
	//		}
	//		else if ((*stack_b)->sorted_index == lower - 2 && !bottom)
	//		{
	//			pa(stack_a, stack_b);
	//			ra(stack_a); // zet onderaan A tot ie boven kan aansluiten
	//			bottom_stack = find_bottom(*stack_a);
	//			bottom = 1;
	//		}
	//		else
	//			rb(stack_b);
	//	}
	//}
}

//void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // 100 nummers 1200 operations
//{
//	int	lower;
//	int	swap;
//	int	bottom;
//	t_node	*bottom_stack = NULL;
//
//	lower = half;
//	swap = 0;
//	bottom = 0;
//	printf("LOWER:%d\n", lower);
//	while (*stack_b && half)
//	{
//		while (half > quarter) // kan in 1 loop: alleen half en kijk naar index voor rrb of niet, quarter = 24 lower = 49
//		{
//			rrb(stack_b);
//			pa(stack_a, stack_b);
//			half--;
//		}
//		half++; // kan dit  optimaler? maakt wss heel weinig uit
//		while (half)
//		{
//			pa(stack_a, stack_b);
//			half--;
//		}
//		while (*stack_b) // kan optimaler
//		{
//			if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1)
//			{
//				if ((*stack_b)->sorted_index == lower - 1) // verkeerde bovenaan
//				{
//					pa(stack_a, stack_b);
//					swap++;
//				}
//				else if (swap) // goede gevonden, zet eronder, lijst klopt, als bottom: zet boven
//				{
//					pa(stack_a, stack_b);
//					sa(stack_a);
//					swap = 0;
//					lower--;
//					if (bottom)
//					{
//						if ((bottom  == 1) && (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1))
//						{
//							rra(stack_a);
//							bottom_stack = NULL;
//							bottom = 0;
//							lower--;
//						}
//						else if (bottom == 2)
//						{
//							if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // verwijder dubbele operaties ff
//							{
//								rra(stack_a);
//								rra(stack_a);
//								sa(stack_a);
//								bottom_stack = NULL;
//								bottom = 0;
//								lower -= 2;
//							}
//							else
//							{
//								rra(stack_a);
//								rra(stack_a);
//								bottom_stack = NULL;
//								bottom = 0;
//								lower -= 2;
//							}
//						}
////						if (bottom_stack->next) // als 2 onderaan, zet beide boven en swap
////						{
////							swap = 1;
////							rra(stack_a);
////							lower--;
////						}
////						rra(stack_a);
////						if (swap)
////							sa(stack_a);
////						swap = 0;
////						bottom_stack = NULL;
////						bottom = 0;
////						lower--;
//						}
//				}
//				else // lijst klopt, gewoon 1 erbij, check of bottom aansluit
//				{
//					pa(stack_a, stack_b);
//					if ((bottom  == 1) && (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1)) // eentje onder, zet boven wanneer goed
//					{
//						rra(stack_a);
//						bottom_stack = NULL;
//						bottom = 0;
//						lower--;
//					}
//					else if (bottom == 2)
//					{
//						if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // verwijder dubbele operaties ff
//						{
//							rra(stack_a);
//							rra(stack_a);
//							sa(stack_a);
//							bottom_stack = NULL;
//							bottom = 0;
//							lower -= 2;
//						}
//						else
//						{
//							rra(stack_a);
//							rra(stack_a);
//							bottom_stack = NULL;
//							bottom = 0;
//							lower -= 2;
//						}
//					}
//					lower--;
//				}
//			}
//			else if ((*stack_b)->sorted_index == lower - 2 && bottom < 2)
//			{
//				if (bottom == 1 && (*stack_b)->sorted_index == bottom_stack->sorted_index - 1)
//				{
//					pa(stack_a, stack_b);
//					ra(stack_a); // zet onderaan A tot ie boven kan aansluiten
//					bottom++;
//				}
//				else if (!bottom)
//				{
//					pa(stack_a, stack_b);
//					ra(stack_a);
//					bottom_stack = find_bottom(*stack_a);
//					bottom++;
//				}
//			}
//			else if ((*stack_b)->sorted_index == lower - 3 && bottom < 2)
//			{
//				if (bottom == 1 && (*stack_b)->sorted_index == bottom_stack->sorted_index + 1)
//				{
//					pa(stack_a, stack_b);
//					ra(stack_a);
//					bottom++;
//				}
//				else if (!bottom)
//				{
//					pa(stack_a, stack_b);
//					ra(stack_a);
//					bottom_stack = find_bottom(*stack_a);
//					bottom++;
//				}
//			}
//			else
//				rb(stack_b);
//		}
//	}
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
