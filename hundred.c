#include "push_swap.h"
#include <stdio.h>

void	big_list_two(t_node **stack_a, t_node **stack_b, int half)
{
	t_stats *data;

	data = alloc_stats(stack_a, stack_b, half);
	if (!data)
		return ;
	data->h = 49;
	data->tq = 24;
	data->three_quarter = 25;

	while (data->stack_a) // alles naar b: 73_50 0-49(random) 74_99
	{
		if ((data->stack_a->sorted_index <= data->tq && \
				data->stack_a->sorted_index >= data->tq - 2) && \
				data->stack_a->sorted_index < data->three_quarter) // 0-24
			upper_quarter_two(data);
		else if ((data->stack_a->sorted_index <= data->h && \
				data->stack_a->sorted_index >= data->h - 2) && \
				data->stack_a->sorted_index >= data->three_quarter) // 25-49
			lower_quarter_two(data);
		else // was niet de goeie
			ra(&data->stack_a);
	}
	*stack_a = NULL;
	*stack_b = data->stack_b;
}

void	upper_quarter_two(t_stats *data)
{
	if (((data->stack_a->sorted_index == data->tq - 1) || (data->stack_a->sorted_index == data->tq - 2)) && data->swap_rot < 2)
	{
		pb(&data->stack_a, &data->stack_b);
		if (!data->swap_rot || (data->swap_rot == 1 && (data->stack_b->sorted_index < data->bottom_stack->sorted_index)))
			data->bottom_stack = data->stack_b;
		rb(&data->stack_b);
		data->swap_rot++;
	}
	else if (data->swap_rot && data->stack_a->sorted_index == data->tq)
		swap_t(data);
	else if (data->stack_a->sorted_index == data->tq)
	{
		pb(&data->stack_a, &data->stack_b);
		rb(&data->stack_b);
		data->tq--;
	}
}

void	lower_quarter_two(t_stats *data)
{
	if ((data->stack_a->sorted_index == data->h - 1 || data->stack_a->sorted_index == data->h - 2) && data->swap < 2)
	{
		pb(&data->stack_a, &data->stack_b);
		data->swap++;
	}
	else if (data->swap && data->stack_a->sorted_index == data->h)
		swop_t(data);
	else if (data->stack_a->sorted_index == data->h)
	{
		pb(&data->stack_a, &data->stack_b);
		data->h--;
	}
}

void	swap_t(t_stats *data)
{
	if ((data->stack_a->sorted_index != data->bottom_stack->sorted_index - 1) || data->swap_rot == 2)
		rrb(&data->stack_b);
	if (data->swap_rot == 2)
		rrb(&data->stack_b);
	pb(&data->stack_a, &data->stack_b);
	rb(&data->stack_b);
	data->bottom_stack = find_bottom(data->stack_b);
	if (data->swap_rot == 2)
	{
		if (data->stack_b->sorted_index < data->stack_b->next->sorted_index)
			sb(&data->stack_b);
		while (data->swap_rot)
		{
			rb(&data->stack_b);
			data->swap_rot--;
			data->tq--;
		}
	}
	else if (data->stack_b->sorted_index == data->bottom_stack->sorted_index - 1)
	{
		rb(&data->stack_b);
		data->tq--;
		data->swap_rot--;
	}
	else
		rb(&data->stack_b);
	data->bottom_stack = find_bottom(data->stack_b);
	data->tq--;
}



void	swop_t(t_stats *data)
{
	if (data->swap == 1)
	{
		pb(&data->stack_a, &data->stack_b);
		sb(&data->stack_b);
		if (data->stack_b->sorted_index == data->stack_b->next->sorted_index - 1)
		{
			data->swap--;
			data->h--;
		}
	}
	else
		swap_two_t(data);
	data->h--;
}

void	swap_two_t(t_stats *data)
{
	rb(&data->stack_b);
	if (data->stack_b->sorted_index == data->stack_a->sorted_index - 1)
	{
		pb(&data->stack_a, &data->stack_b);
		sb(&data->stack_b);
		data->swap--;
		data->h--;
		rrb(&data->stack_b);
		if (data->stack_b->sorted_index == data->stack_b->next->sorted_index - 1)
		{
			data->swap--;
			data->h--;
		}
	}
	else
		more_swap_t(data);
}

void	more_swap_t(t_stats *data)
{
	rb(&data->stack_b);
	pb(&data->stack_a, &data->stack_b);
	rrb(&data->stack_b);
	rrb(&data->stack_b);
	if (data->stack_b->sorted_index == data->stack_b->next->next->sorted_index - 1)
	{
		sb(&data->stack_b);
		data->swap--;
		data->h--;
		if (data->stack_b->sorted_index == data->stack_b->next->sorted_index - 1)
		{
			data->swap--;
			data->h--;
		}
	}
}
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
	}
	while (count)
	{
		rrb(stack_b);
		count--;
	}
	//half--; // naar juiste index
	big_list(stack_a, stack_b, half);
	sorted_to_A(stack_a, stack_b, half, half / 2);
	//big_list_two(stack_b, stack_a, half); // BLBL kinda
	//grow_list(stack_a, stack_b, half, half); // BLGL
	operations = 1;
	return (operations);
}
