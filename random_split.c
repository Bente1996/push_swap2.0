#include "push_swap.h"
#include <stdio.h>

int	random_split(t_node **stack_a, t_node **stack_b, int size)
{
	static 	int	arr[5] = {0};
	int		half;
	int		highest;
	int		h;
	int		operations;
	int		count;

	half = size / 2;
	h = half;
	highest = half;
	count = 0;
	while (h)
	{
		if ((*stack_a)->sorted_index < half) // voeg s toe: NEE geprobeerd
		{
			pb(stack_a, stack_b);
			h--;		
			if (in_group(*stack_b, arr, highest)) // als getal in de groep zit
			{
				highest = move_highest(arr, highest); // verander zoekcriteria op basis van group shift
				printf("naar B: %d\n", (*stack_b)->sorted_index);
				if ((*stack_b)->next)
					rb(stack_b);
				count++;
			}
		}
		else
			ra(stack_a);
	}
	int one = 0;
	int two = 0;
	int three = 0;
	printf("count:%d\n", count);
	printf("%d\n", highest);
	print_list(*stack_b, 'B');
	highest = half - 1;
	while (count)
	{
		rrb(stack_b);
		count--;
		if ((*stack_b)->sorted_index == highest)
		{
			pa(stack_a, stack_b);
			one++;
			highest--;
		}
		else if ((*stack_b)->sorted_index > highest - 5) // als ie wel aan het begin te pakken is
		{
			pa(stack_a, stack_b);
			ra(stack_a);
			one++;
		}
		else if ((*stack_b)->sorted_index < highest - 4 && (*stack_b)->sorted_index > highest - 10)
		{
			pa(stack_a, stack_b);
			two++;
		}
		else if ((*stack_b)->sorted_index < highest  - 10 && (*stack_b)->sorted_index > highest - 15)
		{
			rb(stack_b);
			three++;
		}
	}
	print_list(*stack_b, 'B');
	while (one)
	{
		rrb(stack_b);
		one--;
	}
	while (two)
	{
		pb(stack_a, stack_b);
		two--;
	}
	while (three)
	{
		rra(stack_a);
		pb(stack_a, stack_b);
		three--;
	}
	print_list(*stack_b, 'B');
	half--; // naar juiste index
	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
	operations = count_operations("");
	return (operations);
}

//int	random_split(t_node **stack_a, t_node **stack_b, int size) // werkt al prima
//{
//	static 	int	arr[5] = {0};
//	int		half;
//	int		highest;
//	int		h;
//	int		operations;
//	int		count;
//
//	half = size / 2;
//	h = half;
//	highest = half;
//	count = 0;
//	while (h)
//	{
//		if ((*stack_a)->sorted_index < half) // voeg s toe: NEE geprobeerd
//		{
//			pb(stack_a, stack_b);
//			h--;		
//			if (*stack_b && in_group(*stack_b, arr, highest)) // als getal in de groep zit
//			{
//				highest = move_highest(arr, highest); // verander zoekcriteria op basis van group shift
//				if ((*stack_b)->next)
//					rb(stack_b);
//				count++;
//			}
//		}
//		else
//			ra(stack_a);
//	}
//	while (count)
//	{
//		rrb(stack_b);
//		count--;
//	}
//	half--; // naar juiste index
//	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
//	operations = count_operations("");
//	return (operations);
////}
