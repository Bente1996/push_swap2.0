#include "push_swap.h"
#include <stdio.h>

int	random_split(t_node **stack_a, t_node **stack_b, int size) // bij 500 onder 9000, 100 some boven 100, dus beter zonder optimalisatie
{
	//static 	int	arr[5] = {0};
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
			if ((*stack_b)->sorted_index < highest && (*stack_b)->sorted_index > highest - 31) // kleiner dan 49 en groter dan 34 (49 - 35)
			{
				rb(stack_b);
				count++;
			}
			//if (in_group(*stack_b, arr, highest)) // als getal in de groep zit
			//{
			//	highest = move_highest(arr, highest); // verander zoekcriteria op basis van group shift
			//	printf("naar B: %d\n", (*stack_b)->sorted_index);
			//	if ((*stack_b)->next)
			//		rb(stack_b);
			//	count++;
			//}
		}
		else
			ra(stack_a);
	}
	int one = 0; // 10
	int two = 0; // 10
	printf("count:%d\n", count);
	printf("%d\n", highest);
//	print_list(*stack_b, 'B');
	while (count)
	{
		rrb(stack_b);
		count--;
		if ((*stack_b)->sorted_index > highest - 11) // als ie wel aan het begin te pakken is onderaan A, -1 tot -10
		{
			pa(stack_a, stack_b);
			ra(stack_a);
			one++;
		}
		else if ((*stack_b)->sorted_index < highest - 10 && (*stack_b)->sorted_index > highest - 21) // -11 tot -20
		{
			pa(stack_a, stack_b);
			two++;
		}
	}
	print_list(*stack_a, 'A');
	print_list(*stack_b, 'B');
	int three = 10;
	while (three) // begint bovenaan B
	{
		if ((*stack_b)->sorted_index >= highest - 25) //onderste naar onder
			rb(stack_b);
		else
			pa(stack_a, stack_b); // bovenste naar a
		three--;
	}
	three = 5;
	while (three)
	{
		pb(stack_a, stack_b); // onderste naar boven
		three--;
	}
	three = 5;
	while (three)
	{
		rrb(stack_b); // bovenste naar A: three compleet
		three--;
	}
	while (two)
	{
		if ((*stack_a)->sorted_index >= highest - 15) // staat goed
			ra(stack_a);
		else
			pb(stack_a, stack_b);
		two--;
	}
	two = 5;
	while (two) // two compleet
	{
		rra(stack_a);
		pb(stack_a, stack_b);
		two--;
	}
	while (one)
	{
		rra(stack_a);
		if ((*stack_a)->sorted_index < highest - 5)
			pb(stack_a, stack_b);
		one--;
	}
	one = 5;
	while (one)
	{
		pb(stack_a, stack_b);
		one--;
	}
	print_list(*stack_a, 'A');
	print_list(*stack_b, 'B');
	half--; // naar juiste index
	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
	operations = count_operations("");
	return (operations);
}

//int	random_split(t_node **stack_a, t_node **stack_b, int size) // werkt beter dan die hieronder
//{
//	//static 	int	arr[5] = {0};
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
//			if ((*stack_b)->sorted_index < highest && (*stack_b)->sorted_index > highest - 16) // kleiner dan 49 en groter dan 34 (49 - 35)
//			{
//				rb(stack_b);
//				count++;
//			}
//		}
//		else
//			ra(stack_a);
//	}
//	int one = 0;
//	int two = 0;
//	printf("count:%d\n", count);
//	printf("%d\n", highest);
//	print_list(*stack_b, 'B');
//	while (count)
//	{
//		rrb(stack_b);
//		count--;
//		if ((*stack_b)->sorted_index > highest - 6) // als ie wel aan het begin te pakken is onderaan A, -1 tot -5
//		{
//			pa(stack_a, stack_b);
//			ra(stack_a);
//			one++;
//		}
//		else if ((*stack_b)->sorted_index < highest - 5 && (*stack_b)->sorted_index > highest - 11) // -6 tot -10
//		{
//			pa(stack_a, stack_b);
//			two++;
//		}
//	}
//	print_list(*stack_b, 'B');
//	while (two)
//	{
//		pb(stack_a, stack_b);
//		two--;
//	}
//	while (one)
//	{
//		rra(stack_a);
//		pb(stack_a, stack_b);
//		one--;
//	}
//	print_list(*stack_b, 'B');
//	half--; // naar juiste index
//	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
//	operations = count_operations("");
//	return (operations);
//}

//int	random_split(t_node **stack_a, t_node **stack_b, int size) // werkt al prima, al is 100 nummers wat slechter (net boven 700) dus gebruik niet altijd
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
