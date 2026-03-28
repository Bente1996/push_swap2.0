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
	int n = 15000;
	while (*stack_b && n)
	{
		printf("stack_A: %d\n", (*stack_a)->sorted_index);
		if (bottom_stack)
			printf("bottom:%d  %d\n", bottom_stack->sorted_index, bottom);
		printf("stack_B: %d\n", (*stack_b)->sorted_index);
		printf("lower: %d\n", lower);
		printf("swap:%d\n", swap);
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
										bottom_stack = NULL; // er waren er maar 2
									if (bottom && bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // perfect rijtje
									{
										rra(stack_a);
										bottom--;
										bottom_stack = NULL;
										lower--;
									}

								}
								else // tweede mag niet
								{
									bottom_stack = check_bottom(*stack_a); // vind hoogste van de twee
									if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e mag
									{
										rra(stack_a);
										rra(stack_a); // 2 naar boven en swap
										sa(stack_a);
									}
									if ((*stack_a)->sorted_index != (*stack_a)->next->sorted_index - 1) // check of 2e nu wel goed is
										ra(stack_a); // stuur terug als bovenste fout
									else // nu wel goed rijtje
									{
										bottom--; // naar 0
										bottom_stack = NULL;
										lower--;
									}

							}
							else // eerste was niet goed , dus probeer tweede
							{
								rra(stack_a); // tweede naar boven
								bottom_stack = find_bottom(*stack_a); // kijk wat de derde is
								//sa(stack_a);
								if (bottom_stack->sorted_index == (*stack_a)->next->next->sorted_index - 1) // als de 3e de goede was
								{
									rra(stack_a); // derde naar boven
									sa(stack_a); // derde op tweede plek
									ra(stack_a); // bovenste naar beneden
									sa(stack_a); // derde op goede plek
									bottom_stack = find_bottom(*stack_a);
									if (((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) && \     // als goed rijtje nu
											(bottom_stack->sorted_index == (*stack_a)->sorted_index - 1))
									{
										rra(stack_a);
										bottom -=2;
										lower -= 2;
										bottom_stack = NULL;
									}
									else if ((*stack_a)->sorted_index != (*stack_a)->next->sorted_index - 1) // als bovenste niet goed aansluit
									{
										bottom_stack = find_bottom(*stack_b); // check wat er beneden zit
										if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) // als onderste wel mag
										{
											lower--;
											bottom--;
											rra(stack_a);
											sa(stack_a);
											if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // goed rijtje
											{
												bottom--;
												lower--;
												bottom_stack = NULL;
											}
											else
												ra(stack_a);
											bottom_stack = find_bottom(*stack_a); // nog eentje onder
															      //
															      //
															      // TO BE CONTINUED :)
								}
								else
								{
								}
							}
						}
					}
				}
				lower--;
			}
			else
			{
				pa(stack_a, stack_b);
				if (bottom)
				{
					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
					{
						rra(stack_a); // eerste naar boven
						bottom--;
						lower--;
						if (bottom) // zijn er twee
						{
							bottom_stack = find_bottom(*stack_a);
							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
							{
								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // beiden goed
								{
									rra(stack_a); // tweede naar boven
									bottom--; // naar 0
									bottom_stack = NULL;
									lower--;
								}
							}
							else // eerste was niet goed , dus tweede wel
							{
								rra(stack_a);
								sa(stack_a);
								if (!((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1)) // check of beiden goed  ( != )
								{
									ra(stack_a);
									bottom_stack = find_bottom(*stack_a);
								}
								else
								{
									bottom--; // naar 0
									bottom_stack = NULL; // beiden goed
									lower--;
								}
							}
						}
					}
				}
			}
			lower--;
		}
		else if ((*stack_b)->sorted_index == lower - 2 && bottom < 2)
		{
			pa(stack_a, stack_b);
			ra(stack_a);
			if (!bottom || bottom_stack->sorted_index < bottom_stack->next->sorted_index) // bottom_stack = grootste index
				bottom_stack = find_bottom(*stack_a);
			bottom++;
		}
		else if ((*stack_b)->sorted_index == lower - 3 && bottom < 2)
		{
			pa(stack_a, stack_b);
			ra(stack_a);
			if (!bottom || bottom_stack->sorted_index < bottom_stack->next->sorted_index)
				bottom_stack = find_bottom(*stack_a);
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
		}
		else
			rb(stack_b);
		n--;
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
