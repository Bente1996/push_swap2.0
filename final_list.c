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
				if (bottom)
				{
					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
					{
						rra(stack_a); // eerste naar boven
						bottom--;
						lower--;
						if (bottom) // zijn er twee
						{
							bottom_stack = find_bottom(*stack_a); // deze is over
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
								if (!((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1)) // check of beiden goed 
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
								if (!((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1)) // check of beiden goed 
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
		else
			rb(stack_b);
		n--;
	}
}

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
