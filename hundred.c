#include "push_swap.h"
#include <stdio.h>

int	move_highest(int *arr, int highest)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < 5 && arr[i] != 0)
		sum += arr[i++];
	if (sum == 1)
		highest--;
	else if (sum == 11)
		highest -= 2;
	else if (sum == 111)
		highest -= 3;
	else if (sum == 1111)
		highest -= 4;
	else if (sum == 11111)
		highest -= 5;
	else
		return (highest);
	check_shift(arr, sum); // give right values based on shift 5->4 for sum == 1
	return(highest);
}

void	shift_group(int *arr, int n)
{
	int	shrink;
	int	i;

	i = 0;
	shrink = 1;
	while (i + n < 5)
	{
		if (arr[i + n])
			arr[i] = arr[i + n] - (shrink * 9);
		else
			arr[i] = 0;
		i++;
		shrink *= 10;
	}
}

void	check_shift(int *arr, int sum)
{
	int	i;

	i = 4;
	if (sum == 1) // dan was de tweede dus sowieso niet gevonden, 3e mss wel
		shift_group(arr, 1);
	else if (sum == 11)
		shift_group(arr, 2); 
	else if (sum == 111)
		shift_group(arr, 3);
	else if (sum == 1111)
		shift_group(arr, 4);
	while (sum >= 1) // zet nodige arrays op 0
	{
		arr[i--] = 0;
		sum /= 10;
	}
}

bool	in_group(t_node *stack_b, int *arr, int highest)
{
	if (stack_b->sorted_index == highest - 1)
		arr[0] = 1;
	else if (stack_b->sorted_index == highest - 2)
		arr[1] = 10;
	else if (stack_b->sorted_index == highest - 3)
		arr[2] = 100;
	else if (stack_b->sorted_index == highest - 4)
		arr[3] = 1000;
	else if (stack_b->sorted_index == highest - 5)
		arr[4] = 10000;
	//else if (stack_b->sorted_index < highest - 5 && stack_b->sorted_index > highest - 15) // toegevoegd
	//	return (true);
	else
		return (false);
	return (true);
}


int	random_split(t_node **stack_a, t_node **stack_b, int size) // test: group op A
															   // ipv B
{
	static 	int	arr[5] = {0};
	int		half;
	int		highest;
	int		h;
	int		operations;
	int		count;

	arr[1]++;
	half = size / 2;
	h = half;
	highest = half;
	count = 0;
	printf("%d\n", half);
	while (h)
	{
		if ((*stack_a)->sorted_index < half)
		{
			pb(stack_a, stack_b);
			h--;
		}
		else
			ra(stack_a);
		if (*stack_b && in_group(*stack_b, arr, highest)) // als getal in de groep zit
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
	//half--; // naar juiste index
	//printf("Binnenkomst:\n");
//	print_list(*stack_a, 'A');
//	print_list(*stack_b, 'B');
	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
	sorted_to_A(stack_a, stack_b, half, half / 2);
	grow_list(stack_a, stack_b, half, half);
	operations = 1;
	return (operations);
}
