#include "push_swap.h"
#include <stdio.h>

void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter)
{
	t_node	*bottom_stack;
	int	lower;
	int	swap;
	int	bottom;

	lower = half + 1;
	swap = 0;
	bottom = 0;
	bottom_stack = NULL;
	while (half > quarter)
	{
		rrb(stack_b);
		pa(stack_a, stack_b);
		half--;
	}
	while (half)
	{
		pa(stack_a, stack_b);
		half--;
	}
	while (*stack_b)
	{
		if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1)
		{
			if ((*stack_b)->sorted_index == lower - 1)
			{
				pa(stack_a, stack_b);
				swap++;
				lower++;
			}
			else if (swap)
			{
				pa(stack_a, stack_b);
				sa(stack_a);
				swap = 0;
				if (bottom) // maak 6 switch
				{
					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
					{
						rra(stack_a); // eerste naar boven
						bottom--;
						lower--;
						if (bottom) // zijn er 1 of 2
						{
							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
							{
								bottom_stack = find_bottom(*stack_a); // deze is onder
								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // tweede mag ook
								{
									rra(stack_a); // tweede naar boven
									bottom--; // 0 of 1 over
									lower--;
									if (bottom) // als er 3 waren
										bottom_stack = find_bottom(*stack_a); // de laatste
									else
										bottom_stack = NULL; // er waren er maar 2 [CASE 0.1]
									if (bottom && bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // perfect rijtje [CASE 1]
									{
										rra(stack_a);
										bottom--;
										bottom_stack = NULL;
										lower--;
									} // else: 3e was niet goed [CASE 1 fout]
								}
								else if (bottom == 2) // tweede mag niet, maar zijn er 3
								{
									bottom_stack = check_bottom(*stack_a); // vind hoogste van de twee // maak functie: pak een na laatste
									if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e mag
									{
										rra(stack_a);
										rra(stack_a); // 2 naar boven en swap
										sa(stack_a);
										lower--;
										bottom--;
									}
									if ((*stack_a)->sorted_index != (*stack_a)->next->sorted_index - 1) // check of 2e nu wel goed is
									{
										ra(stack_a); // stuur terug als bovenste fout [CASE 2 fout]
										bottom_stack = find_bottom(*stack_a);
									}
									else // nu wel goed rijtje [CASE 2]
									{
										bottom--; // naar 0
										bottom_stack = NULL;
										lower--;
									}
								} // else: bottom == 1 == [case 0.2]
							}
							else // eerste was niet goed , dus probeer tweede
							{
								rra(stack_a); // tweede naar boven
								if (bottom == 2)
									bottom_stack = find_bottom(*stack_a); // check 3e getal
								else
									bottom_stack = (*stack_a)->next; // als er maar 2 getallen waren, wordt 2 bottom
								if ((*stack_a)->sorted_index == (*stack_a)->next->next->sorted_index - 1) // als tweede goed is
								{
									sa(stack_a); // tweede op goede plek
									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 getallen op juiste plek
									{
										lower--;
										bottom--; // bottom == 1
										if (bottom) // als 3 getallen
										{
											if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e aansluit [CASE 3]
											{
												rra(stack_a); // haal 3e op
												bottom_stack = NULL;
												bottom--; // bottom op 0
												lower--;
											}// else: 3e sluit niet aan [CASE 3 fout], bottom op 1
										}
										else
											bottom_stack = NULL; // maar 2 getallen [CASE 0.3]
									}	
									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) //niet 2 juist, bottom mag als tweede
									{
										rra(stack_a); // haal bottom naar boven, 3 boven
										lower--;
										bottom--; // bottom 1
										sa(stack_a); // twee getallen erop geplakt, 2 iig goed
										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // goed rijtje [CASE: 5]
										{
											lower--;
											bottom--; // bottom naar 0
											bottom_stack = NULL;
										}
										else // fout rijtje [CASE: 5 fout]
										{
											ra(stack_a);
											bottom_stack = find_bottom(*stack_a); // eentje over op bodem
										}
									}
									else // 2e was niet goed
										ra(stack_a);
								}
								else // tweede was niet goed, dus moet wel derde zijn (en dus 3 in totaal)
								{
									rra(stack_a); // haal derde op
									sa(stack_a);
									ra(stack_a); // eentje eraf
									sa(stack_a); // 3e zit goed aangesloten					
									bottom_stack = find_bottom(*stack_a);
									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 op goede plek
									{
										bottom--;
										lower--;
										if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // [CASE 4]
										{
											rra(stack_a);
											bottom--; // gaat naar 0
											lower--;
											bottom_stack = NULL;
										} // else: [CASE 4 fout]
									}
									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) // bottom mag aansluiten als tweede
									{
										rra(stack_a); // haal bottom omhoog
										sa(stack_a);
										lower--;
										bottom--;
										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // perfect rijtje [CASE: 6]
										{
											bottom--;
											lower--;
											bottom_stack = NULL; // alles naar 0
										}
										else // bovenste past niet [CASE: 6 fout]
										{
											ra(stack_a);
											bottom_stack = find_bottom(*stack_a); // zet bottom juist
										}
									}
									else // er was er maar 1 vd 3 goed
									{
										if ((*stack_a)->sorted_index > bottom_stack->sorted_index) // zet hoogste als bottom
											bottom_stack = *stack_a;
										ra(stack_a); // twee beneden
									}
								}		
							}										

                                    // wacht ff
																	  
		
						}
						else // geen bottom over
						     bottom_stack = NULL;
					}
				}
				lower--;
			}
			else
			{
				pa(stack_a, stack_b);
				if (bottom) // maak 6 switch
				{
					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
					{
						rra(stack_a); // eerste naar boven
						bottom--;
						lower--;
						if (bottom) // zijn er 1 of 2
						{
							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
							{
								bottom_stack = find_bottom(*stack_a); // deze is onder
								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // tweede mag ook
								{
									rra(stack_a); // tweede naar boven
									bottom--; // 0 of 1 over
									lower--;
									if (bottom) // als er 3 waren
										bottom_stack = find_bottom(*stack_a); // de laatste
									else
										bottom_stack = NULL; // er waren er maar 2 [CASE 0.1]
									if (bottom && bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // perfect rijtje [CASE 1]
									{
										rra(stack_a);
										bottom--;
										bottom_stack = NULL;
										lower--;
									} // else: 3e was niet goed [CASE 1 fout]
								}
								else if (bottom == 2) // tweede mag niet, maar zijn er 3
								{
									bottom_stack = check_bottom(*stack_a); // vind hoogste van de twee // maak functie: pak een na laatste
									if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e mag
									{
										rra(stack_a);
										rra(stack_a); // 2 naar boven en swap
										sa(stack_a);
										lower--;
										bottom--;
									}
									if ((*stack_a)->sorted_index != (*stack_a)->next->sorted_index - 1) // check of 2e nu wel goed is
									{
										ra(stack_a); // stuur terug als bovenste fout [CASE 2 fout]
										bottom_stack = find_bottom(*stack_a);
									}
									else // nu wel goed rijtje [CASE 2]
									{
										bottom--; // naar 0
										bottom_stack = NULL;
										lower--;
									}
								} // else: bottom == 1 == [case 0.2]
							}
							else // eerste was niet goed , dus probeer tweede
							{
								rra(stack_a); // tweede naar boven
								if (bottom == 2)
									bottom_stack = find_bottom(*stack_a); // check 3e getal
								else
									bottom_stack = (*stack_a)->next; // als er maar 2 getallen waren, wordt 2 bottom
								if ((*stack_a)->sorted_index == (*stack_a)->next->next->sorted_index - 1) // als tweede goed is
								{
									sa(stack_a); // tweede op goede plek
									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 getallen op juiste plek
									{
										lower--;
										bottom--; // bottom == 1
										if (bottom) // als 3 getallen
										{
											if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e aansluit [CASE 3]
											{
												rra(stack_a); // haal 3e op
												bottom_stack = NULL;
												bottom--; // bottom op 0
												lower--;
											}// else: 3e sluit niet aan [CASE 3 fout], bottom op 1
										}
										else
											bottom_stack = NULL; // maar 2 getallen [CASE 0.3]
									}	
									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) //2e niet juist, bottom mag als tweede
									{
										rra(stack_a); // haal bottom naar boven, 3 boven
										lower--;
										bottom--; // bottom 1
										sa(stack_a); // twee getallen erop geplakt, 2 iig goed
										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // goed rijtje [CASE: 5]
										{
											lower--;
											bottom--; // bottom naar 0
											bottom_stack = NULL;
										}
										else // fout rijtje [CASE: 5 fout]
										{
											ra(stack_a);
											bottom_stack = find_bottom(*stack_a); // eentje over op bodem
										}
									}
									else // er waren er maar twee
									     ra(stack_a);
								}
								else // tweede was niet goed, dus moet wel derde zijn (en dus 3 in totaal)
								{
									rra(stack_a); // haal derde op
									sa(stack_a);
									ra(stack_a); // eentje eraf
									sa(stack_a); // 3e zit goed aangesloten					
									bottom_stack = find_bottom(*stack_a);
									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 op goede plek
									{
										bottom--;
										lower--;
										if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // [CASE 4]
										{
											rra(stack_a);
											bottom--; // gaat naar 0
											lower--;
											bottom_stack = NULL;
										} // else: [CASE 4 fout]
									}
									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) // bottom mag aansluiten als tweede
									{
										rra(stack_a); // haal bottom omhoog
										sa(stack_a);
										lower--;
										bottom--;
										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // perfect rijtje [CASE: 6]
										{
											bottom--;
											lower--;
											bottom_stack = NULL; // alles naar 0
										}
										else // bovenste past niet [CASE: 6 fout]
										{
											ra(stack_a);
											bottom_stack = find_bottom(*stack_a); // zet bottom juist
										}
									}
									else // er was er maar 1 vd 3 goed
									{
										if ((*stack_a)->sorted_index > bottom_stack->sorted_index)
											bottom_stack = *stack_a;
										ra(stack_a);
									}

								}		
							}										

                                    // wacht ff
																	  
		
						}
						else // was geen bottom over
						     bottom_stack = NULL;
					}
				}

			}
			lower--;
		}
		else if ((*stack_b)->sorted_index == lower - 2 && bottom < 3)
		{
			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
			{
				pa(stack_a, stack_b);
				ra(stack_a);
				bottom_stack = find_bottom(*stack_a);
			}
			else
			{
				pa(stack_a, stack_b);
				ra(stack_a);
			}
			bottom++;
		}
		else if ((*stack_b)->sorted_index == lower - 3 && bottom < 3)
		{
			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
			{
				pa(stack_a, stack_b);
				ra(stack_a);
				bottom_stack = find_bottom(*stack_a);
			}
			else
			{
				pa(stack_a, stack_b);
				ra(stack_a);
			}
			bottom++;
		}
		else if ((*stack_b)->sorted_index == lower - 4 && bottom < 3)
		{
			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
			{
				pa(stack_a, stack_b);
				ra(stack_a);
				bottom_stack = find_bottom(*stack_a);
			}
			else
			{
				pa(stack_a, stack_b);
				ra(stack_a);
			}
			bottom++;
		}
		else
			rb(stack_b);
	}
}

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
