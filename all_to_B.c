/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   all_to_B.c                                              :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/05/22 17:44:42 by bede-kon            #+#    #+#           */
/*   Updated: 2026/05/22 18:05:24 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_highest_half(t_node **A, t_node **B, int half)
{
	t_stats *data;

	data = alloc_stats(A, B, half);
	if (!data)
		return ;
	while (*A) // alles naar b: 73_50 0-49(random) 74_99
	{
		if ((*A)->n_index >= data->tq && (*A)->n_index <= data->tq + 2) // 75->99
			tq_to_all(data, A, B);
		else if ((*A)->n_index >= data->h && (*A)->n_index <= data->h + 2) // 50->74	
			half_to_tq(data, A, B);
		else // was niet de goeie
			ra(A, 0);
	}
}

void	add_to_bottom(t_stats *data, t_node **A, t_node **B)
{
	if (!(data->swap_rot < 2))
		return ;
	pb(A, B);
	if (!data->swap_rot || \
		(data->swap_rot == 1 && (*B)->n_index > data->bottom_stack->n_index))
		data->bottom_stack = *B;
	rb(B, 0);
	data->swap_rot++;
}

void	tq_to_all(t_stats *data, t_node **A, t_node **B)
{
	if (!((*A)->n_index > data->three_quarter))
		return ;
	if ((*A)->n_index == data->tq)
		grow_tq(data, A, B);
	else if ((*A)->n_index == data->tq + 1 || (*A)->n_index == data->tq + 2)
		add_to_bottom(data, A, B);
}

void	grow_h(t_stats *data, t_node **A, t_node **B)
{
	if (data->swap)
		grow_and_swap_h(data, A, B);
	else
	{
		pb(A, B);
		data->h++;
	}
}

void	half_to_tq(t_stats *data, t_node **A, t_node **B)
{
	if (!((*A)->n_index <= data->three_quarter))
		return ;
	if ((*A)->n_index == data->h)
		grow_h(data, A, B);
	else if ((*A)->n_index == data->h + 1 || (*A)->n_index == data->h + 2)
	{
		if (!(data->swap < 2))
			return ;
		pb(A, B);
		data->swap++;
	}
}

void	sorted_to_A(t_node **A, t_node **B, int half, int quarter)
{
	quarter++;
	while (half > quarter)
	{
		rrb(B);
		pa(A, B, 0);
		half--;
	}
	while (half--)
		pa(A, B, 0);
}

//void	big_list(t_node **stack_a, t_node **stack_b, int half) // werkt met + 2
//															   // WERKT GEWOON
//{
//	int	whole;
//	int	quarter;
//	int	three_quarter;
//	int	tq;
//	int	h;
//	int	swap;
//	int	swap_rot;
//
//	whole = half * 2;
//	quarter = half / 2;
//	three_quarter = whole - quarter;
//	tq = three_quarter + 1;
//	h = half + 1;
//	swap = 0;
//	swap_rot = 0;
////	printf("Tussenstand:\n");
////	printf("Halve:%d\n", half); // 49
////	printf("Kwartje:%d\n", quarter); //24
////	printf("TQ:%d\n", three_quarter); //74
////	print_list(*stack_a, 'A');
////	print_list(*stack_b, 'B');	
//	t_node	*bottom_stack = NULL;
//	while (*stack_a) // alles naar b: 73_50 0-49(random) 74_99
//	{
//		if (((*stack_a)->sorted_index  == tq || ((*stack_a)->sorted_index == tq + 1) || ((*stack_a)->sorted_index == tq + 2)) && (*stack_a)->sorted_index > three_quarter) // 75->99
//		{
//
//			if ((((*stack_a)->sorted_index == tq + 1) || ((*stack_a)->sorted_index == tq + 2)) && swap_rot < 2) // 1 of 2 extra getallen
//			{
//				pb(stack_a, stack_b);
//				if (!swap_rot || (swap_rot == 1 && (*stack_b)->sorted_index > bottom_stack->sorted_index)) // bepaal kleinste index van getallen die nog niet goed staan
//					bottom_stack = *stack_b;
//				rb(stack_b);
//				swap_rot++;
//			}
//			else if (swap_rot && (*stack_a)->sorted_index == tq) // als er iets staat wat er niet hoort
//			{
//				if (((*stack_a)->sorted_index != bottom_stack->sorted_index + 1) || swap_rot == 2) // als degene die er staat niet opvolgt of als er 2 staan
//					rrb(stack_b);
//				if (swap_rot == 2) // 1 of 2 naar benee
//					rrb(stack_b);
//				pb(stack_a, stack_b); // t_q op zn plek gezet
//				rb(stack_b);
//				bottom_stack = find_bottom(*stack_b);
//				if (swap_rot == 2) // swap als bovenste twee getallen verwisseld
//				{
//					if ((*stack_b)->sorted_index > (*stack_b)->next->sorted_index)
//						sb(stack_b);
//					while (swap_rot)
//					{
//						rb(stack_b);
//						swap_rot--; // gaat naar 0
//						tq++;
//					}
//				}
//				else if ((*stack_b)->sorted_index == bottom_stack->sorted_index + 1)
//				{
//					rb(stack_b);
//					tq++;
//					swap_rot--;
//				}
//				else
//					rb(stack_b); // laatste moet toch naar beneden
//				bottom_stack = find_bottom(*stack_b);
//				tq++;
//			}
//			else if ((*stack_a)->sorted_index == tq)// stond niks
//			{
//				pb(stack_a, stack_b); // gewoon even duwen zonder nadenken weetjewel (en beneden zetten)
//				rb(stack_b);
//				tq++;
//			}
//		}
//		else if (((*stack_a)->sorted_index == h || ((*stack_a)->sorted_index == h + 1 ) || ((*stack_a)->sorted_index == h + 2)) && (*stack_a)->sorted_index <= three_quarter) // 50->74	
//		{
//			if ((((*stack_a)->sorted_index == h + 1) || ((*stack_a)->sorted_index == h + 2)) && swap < 2)
//			{
//				pb(stack_a, stack_b);
//				swap++;
//			}
//			else if (swap && (*stack_a)->sorted_index == h) // als er iets staat wat er niet hoort
//			{
//				if (swap == 1)
//				{
//					pb(stack_a, stack_b); // h op zn plek gezet
//					sb(stack_b);
//					if ((*stack_b)->sorted_index == (*stack_b)->next->sorted_index + 1)
//					{
//						swap--;
//						h++;
//					}
//				}
//				else  // als swap == 2
//				{
//					rb(stack_b);
//					if ((*stack_b)->sorted_index == (*stack_a)->sorted_index + 1)
//					{
//						pb(stack_a, stack_b);
//						sb(stack_b);
//						swap--;
//						h++;
//						rrb(stack_b);
//						if ((*stack_b)->sorted_index == (*stack_b)->next->sorted_index + 1)
//						{
//							swap--;
//							h++;
//						}
//					}
//					else
//					{
//						rb(stack_b);
//						pb(stack_a, stack_b);
//						rrb(stack_b);
//						rrb(stack_b);
//						if ((*stack_b)->sorted_index == (*stack_b)->next->next->sorted_index + 1)
//						{
//							sb(stack_b);
//							swap--;
//							h++;
//							if ((*stack_b)->sorted_index == (*stack_b)->next->sorted_index + 1)
//							{
//								swap--;
//								h++;
//							}
//						}
//					}
//
//				}
//				h++;
//			}
//			else if ((*stack_a)->sorted_index == h)// stond niks
//			{
//				pb(stack_a, stack_b); // gewoon even duwen zonder nadenken weetjewel
//				h++;
//			}
//		}
//		else // was niet de goeie
//			ra(stack_a);
//	}
//	final_list(stack_a, stack_b, half, quarter);
//}

