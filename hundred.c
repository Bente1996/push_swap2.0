#include "push_swap.h"
#include <stdio.h>

void	big_list_two(t_node **stack_a, t_node **stack_b, int half) // alles omgedraaid beetje silly, verander namen (three_quarter -> quarter, A vs B)
{
	t_stats *data;

	data = alloc_stats(stack_a, stack_b, half);
	if (!data)
		return ;
	data->three_quarter = data->quarter;
	data->h = half - 1;
	data->tq = 0;
	while (data->stack_b)
	{
		if ((data->stack_b->sorted_index >= data->tq && \
				data->stack_b->sorted_index <= data->tq + 2) && \
				data->stack_b->sorted_index < data->three_quarter) // 0-24
			upper_quarter_two(data);
		else if ((data->stack_b->sorted_index <= data->h && \
				data->stack_b->sorted_index >= data->h - 2) && \
				data->stack_b->sorted_index >= data->three_quarter) // 25-49
			lower_quarter_two(data);
		else // was niet de goeie
			rb(&data->stack_b, 0);
	}
	while (data->quarter--)
		rra(&data->stack_a, 0);
	*stack_b = NULL;
	*stack_a = data->stack_a;
}

void	upper_quarter_two(t_stats *data)
{
	if (((data->stack_b->sorted_index == data->tq + 1) || (data->stack_b->sorted_index == data->tq + 2)) && data->swap_rot < 2)
	{
		pa(&data->stack_a, &data->stack_b, 0);
		if (!data->swap_rot || (data->swap_rot == 1 && (data->stack_a->sorted_index > data->bottom_stack->sorted_index)))
			data->bottom_stack = data->stack_a;
		ra(&data->stack_a, 0);
		data->swap_rot++;
	}
	else if (data->swap_rot && data->stack_b->sorted_index == data->tq)
		swap_t(data);
	else if (data->stack_b->sorted_index == data->tq)
	{
		pa(&data->stack_a, &data->stack_b, 0);
		ra(&data->stack_a, 0);
		data->tq++;
	}
}

void	lower_quarter_two(t_stats *data)
{
	if ((data->stack_b->sorted_index == data->h - 1 || data->stack_b->sorted_index == data->h - 2) && data->swap < 2)
	{
		pa(&data->stack_a, &data->stack_b, 0);
		data->swap++;
	}
	else if (data->swap && data->stack_b->sorted_index == data->h)
		swop_t(data);
	else if (data->stack_b->sorted_index == data->h)
	{
		pa(&data->stack_a, &data->stack_b, 0);
		data->h--;
	}
}

void	swap_t(t_stats *data)
{
	if ((data->stack_b->sorted_index != data->bottom_stack->sorted_index + 1) || data->swap_rot == 2)
		rra(&data->stack_a, 0);
	if (data->swap_rot == 2)
		rra(&data->stack_a, 0);
	pa(&data->stack_a, &data->stack_b, 0);
	ra(&data->stack_a, 0);
	data->bottom_stack = find_bottom(data->stack_a);
	if (data->swap_rot == 2)
	{
		if (data->stack_a->sorted_index > data->stack_a->next->sorted_index)
			sa(&data->stack_a, 0);
		while (data->swap_rot)
		{
			ra(&data->stack_a, 0);
			data->swap_rot--;
			data->tq++;
		}
	}
	else if (data->stack_a->sorted_index == data->bottom_stack->sorted_index + 1)
	{
		ra(&data->stack_a, 0);
		data->tq++;
		data->swap_rot--;
	}
	else
		ra(&data->stack_a, 0);
	data->bottom_stack = find_bottom(data->stack_a);
	data->tq++;
}



void	swop_t(t_stats *data)
{
	if (data->swap == 1)
	{
		pa(&data->stack_a, &data->stack_b, 0);
		sa(&data->stack_a, 0);
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
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
	ra(&data->stack_a, 0);
	if (data->stack_a->sorted_index == data->stack_b->sorted_index - 1)
	{
		pa(&data->stack_a, &data->stack_b, 0);
		sa(&data->stack_a, 0);
		data->swap--;
		data->h--;
		rra(&data->stack_a, 0);
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
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
	ra(&data->stack_a, 0);
	pa(&data->stack_a, &data->stack_b, 0);
	rra(&data->stack_a, 0);
	rra(&data->stack_a, 0);
	if (data->stack_a->sorted_index == data->stack_a->next->next->sorted_index - 1)
	{
		sa(&data->stack_a, 0);
		data->swap--;
		data->h--;
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
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

int	move_quarter(int *arr, int quarter)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < 5 && arr[i] != 0)
		sum += arr[i++];
	if (sum == 1)
		quarter++;
	else if (sum == 11)
		quarter += 2;
	else if (sum == 111)
		quarter += 3;
//	else if (sum == 1111)
//		highest -= 4;
//	else if (sum == 11111)
//		highest -= 5;
	else
		return (quarter);
	check_shift(arr, sum); // give right values based on shift 5->4 for sum == 1
	return(quarter);
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
//	else if (stack_b->sorted_index == highest - 4)
//		arr[3] = 1000;
//	else if (stack_b->sorted_index == highest - 5)
//		arr[4] = 10000;
	//else if (stack_b->sorted_index < highest - 5 && stack_b->sorted_index > highest - 15) // toegevoegd
	//	return (true);
	else
		return (false);
	return (true);
}

bool	in_other_group(t_node *stack_b, int *arr, int quarter)
{
	if (stack_b->sorted_index == quarter)
		arr[0] = 1;
	else if (stack_b->sorted_index == quarter + 1)
		arr[1] = 10;
	else if (stack_b->sorted_index == quarter + 2)
		arr[2] = 100;
//	else if (stack_b->sorted_index == highest - 4)
//		arr[3] = 1000;
//	else if (stack_b->sorted_index == highest - 5)
//		arr[4] = 10000;
	//else if (stack_b->sorted_index < highest - 5 && stack_b->sorted_index > highest - 15) // toegevoegd
	//	return (true);
	else
		return (false);
	return (true);
}

int	random_split(t_node **stack_a, t_node **stack_b, int all) // test: group op A
															   // ipv B
{
	int	arr[5] = {0};
	static	int	array[3];
	int		half;
	int		highest;
	int		h;
      	int		operations;
	int		count;
	int		quarter;

      	half = all / 2;
	h = half;
	highest = half;
	quarter = 0;
	count = 0;
	while (h)
	{
		if ((*stack_a)->sorted_index < half)
		{
			pb(stack_a, stack_b);
			h--;
		}
		else
			ra(stack_a, 0);
		if (*stack_b && in_group(*stack_b, arr, highest)) // als getal in de groep zit
		{
			highest = move_highest(arr, highest); // verander zoekcriteria op basis van group shift
			if ((*stack_b)->next)
				rb(stack_b, 0);
			count++;
		}
		else if (*stack_b && in_other_group(*stack_b, array, quarter))
		{
			quarter = move_quarter(array, quarter);
			if ((*stack_b)->next)
				rb(stack_b, 0);
			count++;
		}
	}
	while (count)
	{
		rrb(stack_b);
		count--;
	}
	big_list(stack_a, stack_b, half);
	if (all % 2)
		sorted_to_A(stack_a, stack_b, half + 1, half / 2);
	else
		sorted_to_A(stack_a, stack_b, half, half / 2);
	big_list_two(stack_a, stack_b, half); // 672 group 5
	operations = 1;
	return (operations);
}
