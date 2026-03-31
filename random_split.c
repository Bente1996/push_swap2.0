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
		if (*stack_b && in_group((*stack_b)->sorted_index, arr, highest)) // als getal in de groep zit
		{
			highest = move_highest(arr, highest); // verander zoekcriteria op basis van group shift
			if ((*stack_b)->next)
				rb(stack_b);
			count++;
			printf("count:%d\n", count);
		}
		//print_list(*stack_b, 'B');
	}
	while (count)
	{
		rrb(stack_b);
		count--;
	}
	half--; // naar juiste index
	printf("Binnenkomst:\n");
//	print_list(*stack_a, 'A');
	print_list(*stack_b, 'B');
	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
	operations = count_operations("");
	return (operations);
}
