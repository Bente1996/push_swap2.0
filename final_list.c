#include "push_swap.h"
#include <stdio.h>

//void	final_list(t_stats *data)
//{
//	int	n;

//	sorted_to_A(data); // alles bovenaan en onderaan B wat gesorteerd was naar A pushen
//	while (data->stack_b)
//	{
//		*stack_a = data->stack_a;
//		*stack_b = data->stack_b;
//		n = find_case((*stack_b)->sorted_index, data->lower, data->bottom);
//		if (n == 1)
//			case_one(data);
//		else if (n == 2) // for -2, -3 en -4 (bottom <3)
//			case_two(data);
//		else // rest
//			rb(&data->stack_b);
//	}
//}

int	find_highest(t_node *stack_b)
{
	int	pos;
	int	highest_pos;
	t_node	*highest;

	pos = 1;
	highest_pos = 1;
	highest = stack_b;
	while (stack_b)
	{
		if (stack_b->value > highest->value)
		{
			highest = stack_b;
			highest_pos = pos;
		}
		stack_b = stack_b->next;
		pos++;
	}
	return (highest_pos);
}

void	highest_to_top(t_node **stack_b)
{
	int	mid_stack;
	int	highest_pos;

	highest_pos = find_highest(*stack_b);
	mid_stack = stack_size(*stack_b) / 2;
	if (mid_stack < highest_pos) // van onderaan
	{
		while (highest_pos <= stack_size(*stack_b))
		{
			rrb(stack_b);
			highest_pos++;
		}
	}
	else // vanaf boven
	{
		while (highest_pos > 1)
		{
			rb(stack_b);
			highest_pos--;
		}
	}
}

t_node	*sort_three(t_node **stack_a, t_node **stack_b)
{
	if ((*stack_b)->sorted_index == 1)
		rb(stack_b);
	if ((*stack_b)->sorted_index == 3) // 321  312
	{
		pa(stack_a, stack_b);
		pa(stack_a, stack_b);
		pa(stack_a, stack_b);
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a);
	}
	else if ((*stack_b)->sorted_index == 2) // 
	{
		pa(stack_a, stack_b);
		if ((*stack_b)->sorted_index == 1)
			sb(stack_b);
		pa(stack_a, stack_b);
		sa(stack_a);
		pa(stack_a, stack_b);
	}
	return (*stack_a);
}

t_node	*sort_top(t_node **stack_a, t_node **stack_b) // selection sort
{
	int n;

	n = 25;
	printf("SORT TOP\n");
	while (n) // voeg functies voor kleine aantallen toe
	{
		if (n == 3)
		{
			*stack_a = sort_three(stack_a, stack_b);
			break ;
		}
		highest_to_top(stack_b);
		pa(stack_a, stack_b);
		n--;
	}
	return (*stack_a);
}

void	swap_B(t_stats *data)
{
	if ((data->stack_b->sorted_index != data->bottom_stack->sorted_index + 1) || data->swap_rot == 2)
		rra(&data->stack_a);
	if (data->swap_rot == 2)
		rra(&data->stack_a);
	pa(&data->stack_a, &data->stack_b);
	ra(&data->stack_a);
	data->bottom_stack = find_bottom(data->stack_a);
	if (data->swap_rot == 2)
	{
		if (data->stack_a->sorted_index > data->stack_a->next->sorted_index)
			sa(&data->stack_a);
		while (data->swap_rot)
		{
			ra(&data->stack_a);
			data->swap_rot--;
			data->tq++;
		}
	}
	else if (data->stack_a->sorted_index == data->bottom_stack->sorted_index + 1)
	{
		ra(&data->stack_a);
		data->tq++;
		data->swap_rot--;
	}
	else
		ra(&data->stack_a);
	data->bottom_stack = find_bottom(data->stack_a);
	data->tq++;
}


void	upper_quarter_B(t_stats *data)
{
	printf("UQ B\n");
	if (((data->stack_b->sorted_index == data->tq + 1) || (data->stack_b->sorted_index == data->tq + 2)) && data->swap_rot < 2)
	{
		pa(&data->stack_a, &data->stack_b);
		if (!data->swap_rot || (data->swap_rot == 1 && (data->stack_a->sorted_index > data->bottom_stack->sorted_index)))
			data->bottom_stack = data->stack_a;
		ra(&data->stack_a);
		data->swap_rot++;
	}
	else if (data->swap_rot && data->stack_b->sorted_index == data->tq)
		swap_B(data);
	else if (data->stack_b->sorted_index == data->tq)
	{
		pa(&data->stack_a, &data->stack_b);
		ra(&data->stack_a);
		data->tq++;
	}
}

void	more_swap_B(t_stats *data)
{
	printf("halloo\n");
	ra(&data->stack_a);
	pa(&data->stack_a, &data->stack_b);
	rra(&data->stack_a);
	rra(&data->stack_a);
	printf("A%d\n", data->stack_a->sorted_index);
	printf("A%d\n", data->stack_a->next->sorted_index);
	printf("A%d\n", data->stack_a->next->next->sorted_index);
	printf("B%d\n", data->stack_b->sorted_index);
	if (data->stack_a->sorted_index == data->stack_a->next->next->sorted_index + 1)
	{
		sa(&data->stack_a);
		printf("swap%d\n", data->swap);
		data->swap--;
		printf("swap%d\n", data->swap);
		data->h++;
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index + 1)
		{
			printf("swap%d\n", data->swap);
			data->swap--;
			printf("swap%d\n", data->swap);
			data->h++;
		}
	}
	else // toegevoegd    HEEEEEEEEEL RAAAAAAAR (zit niet in big_list wtfwtfwtfwtfwtf)
	{
		data->swap -= 2;
		data->h += 2;
	}
}

void	swap_two_B(t_stats *data)
{
	printf("hallootjes\n");
	ra(&data->stack_a);
	if (data->stack_a->sorted_index == data->stack_a->sorted_index + 1)
	{
		pa(&data->stack_a, &data->stack_b);
		sa(&data->stack_a);
		data->swap--;
		data->h++;
		rra(&data->stack_a);
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index + 1)
		{
			data->swap--;
			data->h++;
		}
	}
	else
		more_swap_B(data);
}

void	swop_B(t_stats *data)
{
	printf("halloononon\n");
	if (data->swap == 1)
	{
		pa(&data->stack_a, &data->stack_b);
		sa(&data->stack_a);
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index + 1)
		{
			data->swap--;
			data->h++;
		}
	}
	else
		swap_two_B(data);
	data->h++;
}



void	lower_quarter_B(t_stats *data)
{
	printf("LQ B\n");
	printf("b->sorted_index %d\n", data->stack_b->sorted_index);
	printf("a->sorted_index %d\n", data->stack_a->sorted_index);
	printf("h %d\n", data->h);
	printf("tq %d\n", data->tq);
	printf("swap %d\n", data->swap);
	if ((data->stack_b->sorted_index == data->h + 1 || data->stack_b->sorted_index == data->h + 2) && data->swap < 2)
	{
		printf("1 test\n");
		pa(&data->stack_a, &data->stack_b);
		data->swap++;
	}
	else if (data->swap && data->stack_b->sorted_index == data->h)
	{
		swop_B(data);
		printf("2 test\n");
	}
	else if (data->stack_b->sorted_index == data->h)
	{
		pa(&data->stack_a, &data->stack_b);
		data->h++;
		printf("3 test\n");
	}
	printf("b->sorted_index %d\n", data->stack_b->sorted_index);
	printf("a->sorted_index %d\n", data->stack_a->sorted_index);
	printf("h %d\n", data->h);
	printf("tq %d\n", data->tq);
	printf("swap %d\n\n", data->swap);
}

void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // 2x big_list , gaat iets mis bij tq (126)
{
	t_stats *data;

	sorted_to_A(stack_a, stack_b, half, quarter); // alles bovenaan en onderaan B wat gesorteerd was naar A pushen
	data = alloc_stats(stack_a, stack_b, half - 250);
	if (!data)
		return ;
	data->h = 0;
	data->tq = 125;
	data->three_quarter = 126;
	printf("final list %d %d\n", data->h, data->tq);
	int bente = 4000000;
	while (data->stack_b && bente) // alles naar b: 73_50 0-49(random) 74_99
	{
		if ((data->stack_b->sorted_index >= data->tq && data->stack_b->sorted_index <= data->tq + 2) &&	data->stack_b->sorted_index > data->three_quarter)
			upper_quarter_B(data);
		else if ((data->stack_b->sorted_index >= data->h && data->stack_b->sorted_index <= data->h + 2) && data->stack_b->sorted_index <= data->three_quarter)	
			lower_quarter_B(data);
		else // was niet de goeie
			rb(&data->stack_b);
		bente--;
	}
	if (*stack_b)
		*stack_b = data->stack_b;
	else
		*stack_b = NULL;
	*stack_a = data->stack_a;
	//print_list(data->stack_a, 'A');
	//print_list(data->stack_b, 'B');
}

//void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // werkt normaal
//{
//	t_stats	*data;
//	int	n;
//
//	sorted_to_A(stack_a, stack_b, half, quarter); // alles bovenaan en onderaan B wat gesorteerd was naar A pushen
//	data = alloc_stats(stack_a, stack_b, half);
//	if (!data)
//		return ;
//	while (data->stack_b)
//	{
//		*stack_a = data->stack_a;
////		if (stack_size(data->stack_b) == 25) // toegevoegd
////		{
////			*stack_a = sort_top(&data->stack_a, &data->stack_b);
////			break ;
////		}
//		n = find_case(data->stack_b->sorted_index, data->lower, data->bottom);
//		if (n == 1)
//			case_one(data);
//		else if (n == 2) // for -2, -3 en -4 (bottom <3)
//			case_two(data);
//		else // rest
//			rb(&data->stack_b);
//	}
//	*stack_b = data->stack_b;
//}





		///////////
//		if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1) // == case_one()
//		{
			//if ((*stack_b)->sorted_index == lower - 1)
			//{
			//	pa(stack_a, stack_b);
			//	swap++;
			//	lower++;
			//}
		//	else if (swap)
		//	{
		//		pa(stack_a, stack_b);
		//		sa(stack_a);
		//		swap = 0;
			//	if (bottom) // == handle_bottom()
			//	{
			//		if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
			//		{
				//		rra(stack_a); // eerste naar boven
				//		bottom--;
				//		lower--;
			//			if (bottom) // zijn er 1 of 2    // == more_bottom()
			//			{
			//				if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
			//				{
							//	bottom_stack = find_bottom(*stack_a); // deze is onder
			//					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // tweede mag ook // == add_second()
			//					{
							//		rra(stack_a); // tweede naar boven
							//		bottom--; // 0 of 1 over
							//		lower--;
							//		if (bottom) // als er 3 waren
							//			bottom_stack = find_bottom(*stack_a); // de laatste
							//		else
							//			bottom_stack = NULL; // er waren er maar 2 [CASE 0.1]
							//		if (bottom && bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // perfect rijtje [CASE 1]
							//		{
							//			rra(stack_a);
							//			bottom--;
							//			bottom_stack = NULL;
			//							lower--;
			//						} // else: 3e was niet goed [CASE 1 fout]
			//					}
			//					else if (bottom == 2) // tweede mag niet, maar zijn er 3 // == try_three()
			//					{
							//		bottom_stack = check_bottom(*stack_a); // vind hoogste van de twee // maak functie: pak een na laatste
			//						if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e mag
			//						{
							//			rra(stack_a);
							//			rra(stack_a); // 2 naar boven en swap
							//			sa(stack_a);
							//			lower--;
							//			bottom--;
			//						}
			//						if ((*stack_a)->sorted_index != (*stack_a)->next->sorted_index - 1) // check of 2e nu wel goed is
			//						{
							//			ra(stack_a); // stuur terug als bovenste fout [CASE 2 fout]
							//			bottom_stack = find_bottom(*stack_a);
			//						}
			//						else // nu wel goed rijtje [CASE 2]
			//						{
			//				//			bottom--; // naar 0
							//			bottom_stack = NULL;
							//			lower--;
			//						}
			//					} // else: bottom == 1 == [case 0.2]
			//				}
			//				else // eerste was niet goed , dus probeer tweede // == try_two()
			//				{
					//			rra(stack_a); // tweede naar boven
			//					if (bottom == 2)
					//				bottom_stack = find_bottom(*stack_a); // check 3e getal
			//					else
					//				bottom_stack = (*stack_a)->next; // als er maar 2 getallen waren, wordt 2 bottom
			//					if ((*stack_a)->sorted_index == (*stack_a)->next->next->sorted_index - 1) // als tweede goed is
			//					{
					//				sa(stack_a); // tweede op goede plek
			//						if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 getallen op juiste plek // == check_third() (nog maken)
			//						{
							//			lower--;
							//			bottom--; // bottom == 1
			//							if (bottom) // als 3 getallen
			//							{
			//								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e aansluit [CASE 3]
			//								{
							//					rra(stack_a); // haal 3e op
							//					bottom_stack = NULL;
							//					bottom--; // bottom op 0
							//					lower--;
			//								}// else: 3e sluit niet aan [CASE 3 fout], bottom op 1
			//							}
			//							else
							//				bottom_stack = NULL; // maar 2 getallen [CASE 0.3]
			//						}	
			//						else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) //niet 2 juist, bottom mag als tweede // == get_second () nog maken
			//						{
									//	rra(stack_a); // haal bottom naar boven, 3 boven
									//	lower--;
									//	bottom--; // bottom 1
									//	sa(stack_a); // twee getallen erop geplakt, 2 iig goed
			//							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // goed rijtje [CASE: 5]
			//							{
									//		lower--;
									//		bottom--; // bottom naar 0
									//		bottom_stack = NULL;
			//							}
			//							else // fout rijtje [CASE: 5 fout]
			//							{
									//		ra(stack_a);
									//		bottom_stack = find_bottom(*stack_a); // eentje over op bodem
			//							}
			//						}
			//						else // 2e was niet goed
							//			ra(stack_a);
			//					}
			//					else // tweede was niet goed, dus moet wel derde zijn (en dus 3 in totaal) // == get_third()
			//					{
								//	rra(stack_a); // haal derde op
					////				sa(stack_a);
					////				ra(stack_a); // eentje eraf
					//				sa(stack_a); // 3e zit goed aangesloten					
					//				bottom_stack = find_bottom(*stack_a);
			//						if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 op goede plek
			//						{
					//					bottom--;
					//					lower--;
					//					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // [CASE 4]
			//							{
					//						rra(stack_a);
					//						bottom--; // gaat naar 0
					//						lower--;
					//						bottom_stack = NULL;
			//							} // else: [CASE 4 fout]
			//						}
			//						else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) // bottom mag aansluiten als tweede
			//						{
					//					rra(stack_a); // haal bottom omhoog
					//					sa(stack_a);
					//					lower--;
					//					bottom--;
			//							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // perfect rijtje [CASE: 6]
			//							{
					//						bottom--;
					//						lower--;
					//						bottom_stack = NULL; // alles naar 0
			//							}
			//							else // bovenste past niet [CASE: 6 fout]
					//					{
								//			ra(stack_a);
								//			bottom_stack = find_bottom(*stack_a); // zet bottom juist
			//							}
			//						}
			//						else // er was er maar 1 vd 3 goed
			//						{
								//		if ((*stack_a)->sorted_index > bottom_stack->sorted_index) // zet hoogste als bottom
								//			bottom_stack = *stack_a;
								//		ra(stack_a); // twee beneden
			//						}
			//					}		
			//				}										
			//			}
			//			else // geen bottom over
					//	     bottom_stack = NULL;
			//		}
			//	}
			//	lower--;
			//}
	//		else // == lower maar geen swap
	//		{
	//			pa(stack_a, stack_b);
	//			if (bottom) // maak 6 switch
	//			{
	//				if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
	//				{
//<Down>					rra(stack_a); // eerste naar boven
//						bottom--;
//						lower--;
//						if (bottom) // zijn er 1 of 2
//						{
//							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
//							{
//								bottom_stack = find_bottom(*stack_a); // deze is onder
//								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // tweede mag ook
//								{
//									rra(stack_a); // tweede naar boven
//									bottom--; // 0 of 1 over
//									lower--;
//									if (bottom) // als er 3 waren
//										bottom_stack = find_bottom(*stack_a); // de laatste
//									else
//										bottom_stack = NULL; // er waren er maar 2 [CASE 0.1]
//									if (bottom && bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // perfect rijtje [CASE 1]
//									{
//										rra(stack_a);
//										bottom--;
//										bottom_stack = NULL;
//										lower--;
//									} // else: 3e was niet goed [CASE 1 fout]
//								}
//								else if (bottom == 2) // tweede mag niet, maar zijn er 3
//								{
//									bottom_stack = check_bottom(*stack_a); // vind hoogste van de twee // maak functie: pak een na laatste
//									if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e mag
//									{
//										rra(stack_a);
//										rra(stack_a); // 2 naar boven en swap
//										sa(stack_a);
//										lower--;
//										bottom--;
//									}
//									if ((*stack_a)->sorted_index != (*stack_a)->next->sorted_index - 1) // check of 2e nu wel goed is
//									{
//										ra(stack_a); // stuur terug als bovenste fout [CASE 2 fout]
//										bottom_stack = find_bottom(*stack_a);
//									}
//									else // nu wel goed rijtje [CASE 2]
//									{
//										bottom--; // naar 0
//										bottom_stack = NULL;
//										lower--;
//									}
//								} // else: bottom == 1 == [case 0.2]
//							}
//							else // eerste was niet goed , dus probeer tweede
//							{
//								rra(stack_a); // tweede naar boven
//								if (bottom == 2)
//									bottom_stack = find_bottom(*stack_a); // check 3e getal
//								else
//									bottom_stack = (*stack_a)->next; // als er maar 2 getallen waren, wordt 2 bottom
//								if ((*stack_a)->sorted_index == (*stack_a)->next->next->sorted_index - 1) // als tweede goed is
//								{
//									sa(stack_a); // tweede op goede plek
//									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 getallen op juiste plek
//									{
//										lower--;
//										bottom--; // bottom == 1
//										if (bottom) // als 3 getallen
//										{
//											if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e aansluit [CASE 3]
//											{
//												rra(stack_a); // haal 3e op
//												bottom_stack = NULL;
//												bottom--; // bottom op 0
//												lower--;
//											}// else: 3e sluit niet aan [CASE 3 fout], bottom op 1
//										}
//										else
//											bottom_stack = NULL; // maar 2 getallen [CASE 0.3]
//									}	
//									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) //2e niet juist, bottom mag als tweede
//									{
//										rra(stack_a); // haal bottom naar boven, 3 boven
//										lower--;
//										bottom--; // bottom 1
//										sa(stack_a); // twee getallen erop geplakt, 2 iig goed
//										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // goed rijtje [CASE: 5]
//										{
//											lower--;
//											bottom--; // bottom naar 0
//											bottom_stack = NULL;
//										}
//										else // fout rijtje [CASE: 5 fout]
//										{
//											ra(stack_a);
//											bottom_stack = find_bottom(*stack_a); // eentje over op bodem
//										}
//									}
//									else // er waren er maar twee
//									     ra(stack_a);
//								}
//								else // tweede was niet goed, dus moet wel derde zijn (en dus 3 in totaal)
//								{
//									rra(stack_a); // haal derde op
//									sa(stack_a);
//									ra(stack_a); // eentje eraf
//									sa(stack_a); // 3e zit goed aangesloten					
//									bottom_stack = find_bottom(*stack_a);
//									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 op goede plek
//									{
//										bottom--;
//										lower--;
//										if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // [CASE 4]
//										{
//											rra(stack_a);
//											bottom--; // gaat naar 0
//											lower--;
//											bottom_stack = NULL;
//										} // else: [CASE 4 fout]
//									}
//									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) // bottom mag aansluiten als tweede
//									{
//										rra(stack_a); // haal bottom omhoog
//										sa(stack_a);
//										lower--;
//										bottom--;
//										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // perfect rijtje [CASE: 6]
//										{
//											bottom--;
//											lower--;
//											bottom_stack = NULL; // alles naar 0
//										}
//										else // bovenste past niet [CASE: 6 fout]
//										{
//											ra(stack_a);
//											bottom_stack = find_bottom(*stack_a); // zet bottom juist
//										}
//									}
//									else // er was er maar 1 vd 3 goed
//									{
//										if ((*stack_a)->sorted_index > bottom_stack->sorted_index)
//											bottom_stack = *stack_a;
//										ra(stack_a);
//									}
//								}		
//							}										
//						}
//						else // was geen bottom over
//						     bottom_stack = NULL;
//					}
//				}
//			}
//			lower--;
//		}
//		else if ((*stack_b)->sorted_index == lower - 2 && bottom < 3)
//		{
//			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
//			{
//				pa(stack_a, stack_b);
//				ra(stack_a);
//				bottom_stack = find_bottom(*stack_a);
//			}
//			else
//			{
//				pa(stack_a, stack_b);
//				ra(stack_a);
//			}
//			bottom++;
//		}
//		else if ((*stack_b)->sorted_index == lower - 3 && bottom < 3)
//		{
//			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
//			{
//				pa(stack_a, stack_b);
//				ra(stack_a);
//				bottom_stack = find_bottom(*stack_a);
//			}
//			else
//			{
//				pa(stack_a, stack_b);
//				ra(stack_a);
//			}
//			bottom++;
//		}
//		else if ((*stack_b)->sorted_index == lower - 4 && bottom < 3)
//		{
//			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
//			{
//				pa(stack_a, stack_b);
//				ra(stack_a);
//				bottom_stack = find_bottom(*stack_a);
//			}
//			else
//			{
//				pa(stack_a, stack_b);
//				ra(stack_a);
//			}
//			bottom++;
//		}
//		else
//			rb(stack_b);
//	}
//}
//
////void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // EINDRESULTAAT,ONOPGREBROKEN
//																			  // VERSIE,
//																			  // WERKT!!!
//{
//	t_node	*bottom_stack;
//	int	lower;
//	int	swap;
//	int	bottom;
//
//	lower = half + 1;
//	swap = 0;
//	bottom = 0;
//	bottom_stack = NULL;
//	sorted_to_A(stack_a, stack_b, half, quarter); // alles bovenaan en onderaan B wat gesorteerd was naar A pushen
//	while (*stack_b)
//	{
//		if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1)
//		{
//			if ((*stack_b)->sorted_index == lower - 1)
//			{
//				pa(stack_a, stack_b);
//				swap++;
//				lower++;
//			}
//			else if (swap)
//			{
//				pa(stack_a, stack_b);
//				sa(stack_a);
//				swap = 0;
//				if (bottom) // maak 6 switch
//				{
//					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
//					{
//						rra(stack_a); // eerste naar boven
//						bottom--;
//						lower--;
//						if (bottom) // zijn er 1 of 2
//						{
//							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
//							{
//								bottom_stack = find_bottom(*stack_a); // deze is onder
//								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // tweede mag ook
//								{
//									rra(stack_a); // tweede naar boven
//									bottom--; // 0 of 1 over
//									lower--;
//									if (bottom) // als er 3 waren
//										bottom_stack = find_bottom(*stack_a); // de laatste
//									else
//										bottom_stack = NULL; // er waren er maar 2 [CASE 0.1]
//									if (bottom && bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // perfect rijtje [CASE 1]
//									{
//										rra(stack_a);
//										bottom--;
//										bottom_stack = NULL;
//										lower--;
//									} // else: 3e was niet goed [CASE 1 fout]
//								}
//								else if (bottom == 2) // tweede mag niet, maar zijn er 3
//								{
//									bottom_stack = check_bottom(*stack_a); // vind hoogste van de twee // maak functie: pak een na laatste
//									if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e mag
//									{
//										rra(stack_a);
//										rra(stack_a); // 2 naar boven en swap
//										sa(stack_a);
//										lower--;
//										bottom--;
//									}
//									if ((*stack_a)->sorted_index != (*stack_a)->next->sorted_index - 1) // check of 2e nu wel goed is
//									{
//										ra(stack_a); // stuur terug als bovenste fout [CASE 2 fout]
//										bottom_stack = find_bottom(*stack_a);
//									}
//									else // nu wel goed rijtje [CASE 2]
//									{
//										bottom--; // naar 0
//										bottom_stack = NULL;
//										lower--;
//									}
//								} // else: bottom == 1 == [case 0.2]
//							}
//							else // eerste was niet goed , dus probeer tweede
//							{
//								rra(stack_a); // tweede naar boven
//								if (bottom == 2)
//									bottom_stack = find_bottom(*stack_a); // check 3e getal
//								else
//									bottom_stack = (*stack_a)->next; // als er maar 2 getallen waren, wordt 2 bottom
//								if ((*stack_a)->sorted_index == (*stack_a)->next->next->sorted_index - 1) // als tweede goed is
//								{
//									sa(stack_a); // tweede op goede plek
//									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 getallen op juiste plek
//									{
//										lower--;
//										bottom--; // bottom == 1
//										if (bottom) // als 3 getallen
//										{
//											if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e aansluit [CASE 3]
//											{
//												rra(stack_a); // haal 3e op
//												bottom_stack = NULL;
//												bottom--; // bottom op 0
//												lower--;
//											}// else: 3e sluit niet aan [CASE 3 fout], bottom op 1
//										}
//										else
//											bottom_stack = NULL; // maar 2 getallen [CASE 0.3]
//									}	
//									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) //niet 2 juist, bottom mag als tweede
//									{
//										rra(stack_a); // haal bottom naar boven, 3 boven
//										lower--;
//										bottom--; // bottom 1
//										sa(stack_a); // twee getallen erop geplakt, 2 iig goed
//										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // goed rijtje [CASE: 5]
//										{
//											lower--;
//											bottom--; // bottom naar 0
//											bottom_stack = NULL;
//										}
//										else // fout rijtje [CASE: 5 fout]
//										{
//											ra(stack_a);
//											bottom_stack = find_bottom(*stack_a); // eentje over op bodem
//										}
//									}
//									else // 2e was niet goed
//										ra(stack_a);
//								}
//								else // tweede was niet goed, dus moet wel derde zijn (en dus 3 in totaal)
//								{
//									rra(stack_a); // haal derde op
//									sa(stack_a);
//									ra(stack_a); // eentje eraf
//									sa(stack_a); // 3e zit goed aangesloten					
//									bottom_stack = find_bottom(*stack_a);
//									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 op goede plek
//									{
//										bottom--;
//										lower--;
//										if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // [CASE 4]
//										{
//											rra(stack_a);
//											bottom--; // gaat naar 0
//											lower--;
//											bottom_stack = NULL;
//										} // else: [CASE 4 fout]
//									}
//									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) // bottom mag aansluiten als tweede
//									{
//										rra(stack_a); // haal bottom omhoog
//										sa(stack_a);
//										lower--;
//										bottom--;
//										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // perfect rijtje [CASE: 6]
//										{
//											bottom--;
//											lower--;
//											bottom_stack = NULL; // alles naar 0
//										}
//										else // bovenste past niet [CASE: 6 fout]
//										{
//											ra(stack_a);
//											bottom_stack = find_bottom(*stack_a); // zet bottom juist
//										}
//									}
//									else // er was er maar 1 vd 3 goed
//									{
//										if ((*stack_a)->sorted_index > bottom_stack->sorted_index) // zet hoogste als bottom
//											bottom_stack = *stack_a;
//										ra(stack_a); // twee beneden
//									}
//								}		
//							}										
//						}
//						else // geen bottom over
//						     bottom_stack = NULL;
//					}
//				}
//				lower--;
//			}
//			else
//			{
//				pa(stack_a, stack_b);
//				if (bottom) // maak 6 switch
//				{
//					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
//					{
//						rra(stack_a); // eerste naar boven
//						bottom--;
//						lower--;
//						if (bottom) // zijn er 1 of 2
//						{
//							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
//							{
//								bottom_stack = find_bottom(*stack_a); // deze is onder
//								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // tweede mag ook
//								{
//									rra(stack_a); // tweede naar boven
//									bottom--; // 0 of 1 over
//									lower--;
//									if (bottom) // als er 3 waren
//										bottom_stack = find_bottom(*stack_a); // de laatste
//									else
//										bottom_stack = NULL; // er waren er maar 2 [CASE 0.1]
//									if (bottom && bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // perfect rijtje [CASE 1]
//									{
//										rra(stack_a);
//										bottom--;
//										bottom_stack = NULL;
//										lower--;
//									} // else: 3e was niet goed [CASE 1 fout]
//								}
//								else if (bottom == 2) // tweede mag niet, maar zijn er 3
//								{
//									bottom_stack = check_bottom(*stack_a); // vind hoogste van de twee // maak functie: pak een na laatste
//									if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e mag
//									{
//										rra(stack_a);
//										rra(stack_a); // 2 naar boven en swap
//										sa(stack_a);
//										lower--;
//										bottom--;
//									}
//									if ((*stack_a)->sorted_index != (*stack_a)->next->sorted_index - 1) // check of 2e nu wel goed is
//									{
//										ra(stack_a); // stuur terug als bovenste fout [CASE 2 fout]
//										bottom_stack = find_bottom(*stack_a);
//									}
//									else // nu wel goed rijtje [CASE 2]
//									{
//										bottom--; // naar 0
//										bottom_stack = NULL;
//										lower--;
//									}
//								} // else: bottom == 1 == [case 0.2]
//							}
//							else // eerste was niet goed , dus probeer tweede
//							{
//								rra(stack_a); // tweede naar boven
//								if (bottom == 2)
//									bottom_stack = find_bottom(*stack_a); // check 3e getal
//								else
//									bottom_stack = (*stack_a)->next; // als er maar 2 getallen waren, wordt 2 bottom
//								if ((*stack_a)->sorted_index == (*stack_a)->next->next->sorted_index - 1) // als tweede goed is
//								{
//									sa(stack_a); // tweede op goede plek
//									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 getallen op juiste plek
//									{
//										lower--;
//										bottom--; // bottom == 1
//										if (bottom) // als 3 getallen
//										{
//											if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e aansluit [CASE 3]
//											{
//												rra(stack_a); // haal 3e op
//												bottom_stack = NULL;
//												bottom--; // bottom op 0
//												lower--;
//											}// else: 3e sluit niet aan [CASE 3 fout], bottom op 1
//										}
//										else
//											bottom_stack = NULL; // maar 2 getallen [CASE 0.3]
//									}	
//									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) //2e niet juist, bottom mag als tweede
//									{
//										rra(stack_a); // haal bottom naar boven, 3 boven
//										lower--;
//										bottom--; // bottom 1
//										sa(stack_a); // twee getallen erop geplakt, 2 iig goed
//										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // goed rijtje [CASE: 5]
//										{
//											lower--;
//											bottom--; // bottom naar 0
//											bottom_stack = NULL;
//										}
//										else // fout rijtje [CASE: 5 fout]
//										{
//											ra(stack_a);
//											bottom_stack = find_bottom(*stack_a); // eentje over op bodem
//										}
//									}
//									else // er waren er maar twee
//									     ra(stack_a);
//								}
//								else // tweede was niet goed, dus moet wel derde zijn (en dus 3 in totaal)
//								{
//									rra(stack_a); // haal derde op
//									sa(stack_a);
//									ra(stack_a); // eentje eraf
//									sa(stack_a); // 3e zit goed aangesloten					
//									bottom_stack = find_bottom(*stack_a);
//									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 op goede plek
//									{
//										bottom--;
//										lower--;
//										if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // [CASE 4]
//										{
//											rra(stack_a);
//											bottom--; // gaat naar 0
//											lower--;
//											bottom_stack = NULL;
//										} // else: [CASE 4 fout]
//									}
//									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) // bottom mag aansluiten als tweede
//									{
//										rra(stack_a); // haal bottom omhoog
//										sa(stack_a);
//										lower--;
//										bottom--;
//										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // perfect rijtje [CASE: 6]
//										{
//											bottom--;
//											lower--;
//											bottom_stack = NULL; // alles naar 0
//										}
//										else // bovenste past niet [CASE: 6 fout]
//										{
//											ra(stack_a);
//											bottom_stack = find_bottom(*stack_a); // zet bottom juist
//										}
//									}
//									else // er was er maar 1 vd 3 goed
//									{
//										if ((*stack_a)->sorted_index > bottom_stack->sorted_index)
//											bottom_stack = *stack_a;
//										ra(stack_a);
//									}
//								}		
//							}										
//						}
//						else // was geen bottom over
//						     bottom_stack = NULL;
//					}
//				}
//			}
//			lower--;
//		}
//		else if ((*stack_b)->sorted_index == lower - 2 && bottom < 3)
//		{
//			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
//			{
//				pa(stack_a, stack_b);
//				ra(stack_a);
//				bottom_stack = find_bottom(*stack_a);
//			}
//			else
//			{
//				pa(stack_a, stack_b);
//				ra(stack_a);
//			}
//			bottom++;
//		}
//		else if ((*stack_b)->sorted_index == lower - 3 && bottom < 3)
//		{
//			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
//			{
//				pa(stack_a, stack_b);
//				ra(stack_a);
//				bottom_stack = find_bottom(*stack_a);
//			}
//			else
//			{
//				pa(stack_a, stack_b);
//				ra(stack_a);
//			}
//			bottom++;
//		}
//		else if ((*stack_b)->sorted_index == lower - 4 && bottom < 3)
//		{
//			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
//			{
//				pa(stack_a, stack_b);
//				ra(stack_a);
//				bottom_stack = find_bottom(*stack_a);
//			}
//			else
//			{
//				pa(stack_a, stack_b);
//				ra(stack_a);
//			}
//			bottom++;
//		}
//		else
//			rb(stack_b);
//	}
//}

//void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // 2 bottom: WERKT :D
//{
//	t_node	*bottom_stack;
//	int	lower;
//	int	swap;
//	int	bottom;
//
//	lower = half + 1;
//	swap = 0;
//	bottom = 0;
//	bottom_stack = NULL;
//	while (half > quarter)
//	{
//		rrb(stack_b);
//		pa(stack_a, stack_b);
//		half--;
//	}
//	while (half)
//	{
//		pa(stack_a, stack_b);
//		half--;
//	}
//	int n = 15000;
//	while (*stack_b && n)
//	{
//		printf("stack_A: %d\n", (*stack_a)->sorted_index);
//		if (bottom_stack)
//			printf("bottom:%d  %d\n", bottom_stack->sorted_index, bottom);
//		printf("stack_B: %d\n", (*stack_b)->sorted_index);
//		printf("lower: %d\n", lower);
//		printf("swap:%d\n", swap);
//		if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1)
//		{
//			if ((*stack_b)->sorted_index == lower - 1)
//			{
//				pa(stack_a, stack_b);
//				swap++;
//				lower++;
//			}
//			else if (swap)
//			{
//				pa(stack_a, stack_b);
//				sa(stack_a);
//				swap = 0;
//				if (bottom)
//				{
//					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
//					{
//						rra(stack_a); // eerste naar boven
//						bottom--;
//						lower--;
//						if (bottom) // zijn er twee
//						{
//							bottom_stack = find_bottom(*stack_a); // deze is over
//							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
//							{
//								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // beiden goed
//								{
//									rra(stack_a); // tweede naar boven
//									bottom--; // naar 0
//									bottom_stack = NULL;
//									lower--;
//								}
//							}
//							else // eerste was niet goed , dus tweede wel
//							{
//								rra(stack_a);
//								sa(stack_a);
//								if (!((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1)) // check of beiden goed  ( != )
//								{
//									ra(stack_a);
//									bottom_stack = find_bottom(*stack_a);
//								}
//								else
//								{
//									bottom--; // naar 0
//									bottom_stack = NULL; // beiden goed
//									lower--;
//								}
//							}
//						}
//					}
//				}
//				lower--;
//			}
//			else
//			{
//				pa(stack_a, stack_b);
//				if (bottom)
//				{
//					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
//					{
//						rra(stack_a); // eerste naar boven
//						bottom--;
//						lower--;
//						if (bottom) // zijn er twee
//						{
//							bottom_stack = find_bottom(*stack_a);
//							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
//							{
//								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // beiden goed
//								{
//									rra(stack_a); // tweede naar boven
//									bottom--; // naar 0
//									bottom_stack = NULL;
//									lower--;
//								}
//							}
//							else // eerste was niet goed , dus tweede wel
//							{
//								rra(stack_a);
//								sa(stack_a);
//								if (!((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1)) // check of beiden goed ( != )
//								{
//									ra(stack_a);
//									bottom_stack = find_bottom(*stack_a);
//								}
//								else
//								{
//									bottom--; // naar 0
//									bottom_stack = NULL; // beiden goed
//									lower--;
//								}
//							}
//						}
//					}
//				}
//			}
//			lower--;
//		}
//		else if ((*stack_b)->sorted_index == lower - 2 && bottom < 2)
//		{
//			pa(stack_a, stack_b);
//			ra(stack_a);
//			if (!bottom || bottom_stack->sorted_index < bottom_stack->next->sorted_index) // bottom_stack = grootste index
//				bottom_stack = find_bottom(*stack_a);
//			bottom++;
//		}
//		else if ((*stack_b)->sorted_index == lower - 3 && bottom < 2)
//		{
//			pa(stack_a, stack_b);
//			ra(stack_a);
//			if (!bottom || bottom_stack->sorted_index < bottom_stack->next->sorted_index)
//				bottom_stack = find_bottom(*stack_a);
//			bottom++;
//		}
//		else
//			rb(stack_b);
//		n--;
//	}
//}

//void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // 1 bottom: WERKT
//{
//	t_node	*bottom_stack;
//	int	lower;
//	int	swap;
//	int	bottom;
//
//	lower = half + 1;
//	swap = 0;
//	bottom = 0;
//	bottom_stack = NULL;
//	while (half > quarter)
//	{
//		rrb(stack_b);
//		pa(stack_a, stack_b);
//		half--;
//	}
//	while (half)
//	{
//		pa(stack_a, stack_b);
//		half--;
//	}
//	int n = 100000;
//	while (*stack_b && n)
//	{
//		printf("stack_B: %d\n", (*stack_b)->sorted_index);
//		printf("lower: %d\n", lower);
//		if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1)
//		{
//			if ((*stack_b)->sorted_index == lower - 1)
//			{
//				pa(stack_a, stack_b);
//				swap++;
//				lower++;
//			}
//			else if (swap)
//			{
//				pa(stack_a, stack_b);
//				sa(stack_a);
//				swap = 0;
//				if (bottom)
//				{
//					rra(stack_a);
//					bottom = 0;
//					bottom_stack = NULL;
//					lower--;
//				}
//				lower--;
//			}
//			else
//			{
//				pa(stack_a, stack_b);
//				if (bottom && bottom_stack->sorted_index == (*stack_a)->sorted_index - 1)
//				{
//					rra(stack_a);
//					bottom = 0;
//					bottom_stack = NULL;
//					lower--;
//				}
//			}
//			lower--;
//		}
//		else if ((*stack_b)->sorted_index == lower - 2 && !bottom)
//		{
//			pa(stack_a, stack_b);
//			ra(stack_a);
//			bottom = 1;
//			bottom_stack = find_bottom(*stack_a);
//		}
//		else
//			rb(stack_b);
//		n--;
//	}
//}
