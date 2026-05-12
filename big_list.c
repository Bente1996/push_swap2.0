#include "push_swap.h"
#include <stdio.h>

void	big_list(t_node **stack_a, t_node **stack_b, int half) // werkt met + 2
{
	t_stats *data;

	data = alloc_stats(stack_a, stack_b, half);
	if (!data)
		return ;
	printf("h big_list: %d\n", data->h);
	printf("tq big_list: %d\n", data->tq);
	printf("three quarter big_list: %d\n", data->three_quarter);

	while (data->stack_a) // alles naar b: 73_50 0-49(random) 74_99
	{
		printf("testje\n");
		if ((data->stack_a->sorted_index >= data->tq && \
				data->stack_a->sorted_index <= data->tq + 2) && \
				data->stack_a->sorted_index > data->three_quarter) // 75->99
			upper_quarter(data);
		else if ((data->stack_a->sorted_index >= data->h && \
				data->stack_a->sorted_index <= data->h + 2) && \
				data->stack_a->sorted_index <= data->three_quarter) // 50->74	
			lower_quarter(data);
		else // was niet de goeie
			ra(&data->stack_a);
	}
	*stack_a = NULL;
	*stack_b = data->stack_b;
}

void	upper_quarter(t_stats *data)
{
	if (((data->stack_a->sorted_index == data->tq + 1) || (data->stack_a->sorted_index == data->tq + 2)) && data->swap_rot < 2)
	{
		pb(&data->stack_a, &data->stack_b);
		if (!data->swap_rot || (data->swap_rot == 1 && (data->stack_b->sorted_index > data->bottom_stack->sorted_index)))
			data->bottom_stack = data->stack_b;
		rb(&data->stack_b);
		data->swap_rot++;
	}
	else if (data->swap_rot && data->stack_a->sorted_index == data->tq)
		swap(data);
	else if (data->stack_a->sorted_index == data->tq)
	{
		pb(&data->stack_a, &data->stack_b);
		rb(&data->stack_b);
		data->tq++;
	}
}

void	lower_quarter(t_stats *data)
{
	if ((data->stack_a->sorted_index == data->h + 1 || data->stack_a->sorted_index == data->h + 2) && data->swap < 2)
	{
		pb(&data->stack_a, &data->stack_b);
		data->swap++;
	}
	else if (data->swap && data->stack_a->sorted_index == data->h)
		swop(data);
	else if (data->stack_a->sorted_index == data->h)
	{
		pb(&data->stack_a, &data->stack_b);
		data->h++;
	}
}

void	sorted_to_A(t_node **A, t_node **B, int half, int quarter)
{
	printf("half in sorted to a: %d\n", half);
	printf("half in sorted to a: %d\n", quarter);
	quarter++;
	while (half > quarter)
	{
		rrb(B);
		pa(A, B);
		half--;
	}
	while (half)
	{
		pa(A, B);
		half--;
	}
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

