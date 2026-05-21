#include "push_swap.h"
#include <stdio.h>

void	all_to_A(t_node **A, t_node **B, int half) // verander namen (three_quarter -> quarter, A vs B)
{
	t_stats *data;

	data = alloc_stats(A, B, half);
	if (!data)
		return ;
	data->three_quarter = data->quarter;
	data->h = half - 1;
	data->tq = 0;
	while (*B)
	{
		if (((*B)->n_index >= data->tq && \
				(*B)->n_index <= data->tq + 2) && \
				(*B)->n_index < data->three_quarter) // 0-24
			upper_quarter_two(data, A, B);
		else if (((*B)->n_index <= data->h && \
				(*B)->n_index >= data->h - 2) && \
				(*B)->n_index >= data->three_quarter) // 25-49
			lower_quarter_two(data, A, B);
		else // was niet de goeie
			rb(B, 0);
	}
	while (data->quarter--)
		rra(A, 0);
}

void	upper_quarter_two(t_stats *data, t_node **A, t_node **B)
{
	if ((((*B)->n_index == data->tq + 1) || ((*B)->n_index == data->tq + 2)) && data->swap_rot < 2)
	{
		pa(A, B, 0);
		if (!data->swap_rot || (data->swap_rot == 1 && ((*A)->n_index > data->bottom_stack->n_index)))
			data->bottom_stack = *A;
		ra(A, 0);
		data->swap_rot++;
	}
	else if (data->swap_rot && (*B)->n_index == data->tq)
		swap_t(data, A, B);
	else if ((*B)->n_index == data->tq)
	{
		pa(A, B, 0);
		ra(A, 0);
		data->tq++;
	}
}

void	lower_quarter_two(t_stats *data, t_node **A, t_node **B)
{
	if (((*B)->n_index == data->h - 1 || (*B)->n_index == data->h - 2) && data->swap < 2)
	{
		pa(A, B, 0);
		data->swap++;
	}
	else if (data->swap && (*B)->n_index == data->h)
		swop_t(data, A, B);
	else if ((*B)->n_index == data->h)
	{
		pa(A, B, 0);
		data->h--;
	}
}

void	swap_t(t_stats *data, t_node **A, t_node **B)
{
	if (((*B)->n_index != data->bottom_stack->n_index + 1) || data->swap_rot == 2)
		rra(A, 0);
	if (data->swap_rot == 2)
		rra(A, 0);
	pa(A, B, 0);
	ra(A, 0);
	data->bottom_stack = find_bottom(*A);
	if (data->swap_rot == 2)
	{
		if ((*A)->n_index > (*A)->next->n_index)
			sa(A, 0);
		while (data->swap_rot)
		{
			ra(A, 0);
			data->swap_rot--;
			data->tq++;
		}
	}
	else if ((*A)->n_index == data->bottom_stack->n_index + 1)
	{
		ra(A, 0);
		data->tq++;
		data->swap_rot--;
	}
	else
		ra(A, 0);
	data->bottom_stack = find_bottom(*A);
	data->tq++;
}

void	swop_t(t_stats *data, t_node **A, t_node **B)
{
	if (data->swap == 1)
	{
		pa(A, B, 0);
		sa(A, 0);
		if ((*A)->n_index == (*A)->next->n_index - 1)
		{
			data->swap--;
			data->h--;
		}
	}
	else
		swap_two_t(data, A, B);
	data->h--;
}

void	swap_two_t(t_stats *data, t_node **A, t_node **B)
{
	ra(A, 0);
	if ((*A)->n_index == (*B)->n_index - 1)
	{
		pa(A, B, 0);
		sa(A, 0);
		data->swap--;
		data->h--;
		rra(A, 0);
		if ((*A)->n_index == (*A)->next->n_index - 1)
		{
			data->swap--;
			data->h--;
		}
	}
	else
		more_swap_t(data, A, B);
}

void	more_swap_t(t_stats *data, t_node **A, t_node **B)
{
	ra(A, 0);
	pa(A, B, 0);
	rra(A, 0);
	rra(A, 0);
	if ((*A)->n_index == (*A)->next->next->n_index - 1)
	{
		sa(A, 0);
		data->swap--;
		data->h--;
		if ((*A)->n_index == (*A)->next->n_index - 1)
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
	while (i < 3 && arr[i] != 0)
		sum += arr[i++];
	if (sum == 1)
		highest--;
	else if (sum == 11)
		highest -= 2;
	else if (sum == 111)
		highest -= 3;
	else
		return (highest);
	check_shift(arr, sum); // give right values based on shift 5->4 for sum == 1
	return(highest);
}

int	move_lowest(int *arr, int lowest)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < 3 && arr[i] != 0) // 5 naar 3 veranderen
		sum += arr[i++];
	if (sum == 1)
		lowest++;
	else if (sum == 11)
		lowest += 2;
	else if (sum == 111)
		lowest += 3;
	else
		return (lowest);
	check_shift(arr, sum); // give right values based on shift 5->4 for sum == 1
	return(lowest);
}

void	shift_group(int *arr, int n)
{
	int	shrink;
	int	i;

	i = 0;
	shrink = 1;
	while (i + n < 3) // 5 naar 3 veranderen
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

	i = 2;
	if (sum == 1) // dan was de tweede dus sowieso niet gevonden, 3e mss wel
		shift_group(arr, 1);
	else if (sum == 11)
		shift_group(arr, 2); 
	else if (sum == 111)
		shift_group(arr, 3);
	while (sum >= 1) // zet nodige arrays op 0
	{
		arr[i--] = 0;
		sum /= 10;
	}
}

bool	highest_group(t_node *B, int *arr, int highest)
{
	if (B->n_index == highest - 1)
		arr[0] = 1;
	else if (B->n_index == highest - 2)
		arr[1] = 10;
	else if (B->n_index == highest - 3)
		arr[2] = 100;
	else
		return (false);
	return (true);
}

bool	lowest_group(t_node *B, int *arr, int lowest)
{
	if (B->n_index == lowest)
		arr[0] = 1;
	else if (B->n_index == lowest + 1)
		arr[1] = 10;
	else if (B->n_index == lowest + 2)
		arr[2] = 100;
	else
		return (false);
	return (true);
}

bool	little_organise(t_node **B, int half)
{
	int	arr[3];
	int	array[3];
	int	top;

	top = 0;
	if (*B && highest_group(*B, arr, half)) // als getal in de groep zit
	{
		half = move_highest(arr, half); // verander zoekcriteria op basis van group shift
		if ((*B)->next) // WAAROM??!?!??!??!!?
			rb(B, 0);
		return (true);
	}
	else if (*B && lowest_group(*B, array, top))
	{
		top = move_lowest(array, top);
		if ((*B)->next)
			rb(B, 0);
		return (true);
	}
	return (false);
}

void	split_list(t_node **A, t_node **B, int half)
{
	int	h;
	int	count;

	h = half;
	count = 0;
	while (h)
	{
		if ((*A)->n_index < half)
		{
			pb(A, B);
			h--;
		}
		else
			ra(A, 0);
		if (little_organise(B, half))
			count++;
	}
	while (count--)
		rrb(B);
}

void	sort_medium_list(t_node **A, t_node **B, int all)
{
	int		half;

	half = all / 2;
	split_list(A, B, all / 2);
	all_to_B(A, B, half);
	if (UNEVEN)
		sorted_to_A(A, B, half + 1, half / 2);
	else
		sorted_to_A(A, B, half, half / 2);
	all_to_A(A, B, half);
	return ;
}
