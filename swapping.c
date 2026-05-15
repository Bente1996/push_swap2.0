#include "push_swap.h"

void	swap(t_stats *data)
{
	if ((data->stack_a->sorted_index != data->bottom_stack->sorted_index + 1) || data->swap_rot == 2)
		rrb(&data->stack_b);
	if (data->swap_rot == 2)
		rrb(&data->stack_b);
	pb(&data->stack_a, &data->stack_b);
	rb(&data->stack_b, 0);
	data->bottom_stack = find_bottom(data->stack_b);
	if (data->swap_rot == 2)
	{
		if (data->stack_b->sorted_index > data->stack_b->next->sorted_index)
			sb(&data->stack_b);
		while (data->swap_rot)
		{
			rb(&data->stack_b, 0);
			data->swap_rot--;
			data->tq++;
		}
	}
	else if (data->stack_b->sorted_index == data->bottom_stack->sorted_index + 1)
	{
		rb(&data->stack_b, 0);
		data->tq++;
		data->swap_rot--;
	}
	else
		rb(&data->stack_b, 0);
	data->bottom_stack = find_bottom(data->stack_b);
	data->tq++;
}



void	swop(t_stats *data)
{
	if (data->swap == 1)
	{
		pb(&data->stack_a, &data->stack_b);
		sb(&data->stack_b);
		if (data->stack_b->sorted_index == data->stack_b->next->sorted_index + 1)
		{
			data->swap--;
			data->h++;
		}
	}
	else
		swap_two(data);
	data->h++;
}

void	swap_two(t_stats *data)
{
	rb(&data->stack_b, 0);
	if (data->stack_b->sorted_index == data->stack_a->sorted_index + 1)
	{
		pb(&data->stack_a, &data->stack_b);
		sb(&data->stack_b);
		data->swap--;
		data->h++;
		rrb(&data->stack_b);
		if (data->stack_b->sorted_index == data->stack_b->next->sorted_index + 1)
		{
			data->swap--;
			data->h++;
		}
	}
	else
		more_swap(data);
}

void	more_swap(t_stats *data)
{
	rb(&data->stack_b, 0);
	pb(&data->stack_a, &data->stack_b);
	rrb(&data->stack_b);
	rrb(&data->stack_b);
	if (data->stack_b->sorted_index == data->stack_b->next->next->sorted_index + 1)
	{
		sb(&data->stack_b);
		data->swap--;
		data->h++;
		if (data->stack_b->sorted_index == data->stack_b->next->sorted_index + 1)
		{
			data->swap--;
			data->h++;
		}
	}
}
