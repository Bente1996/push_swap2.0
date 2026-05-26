/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   all_to_A.c                                              :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/05/22 17:56:04 by bede-kon            #+#    #+#           */
/*   Updated: 2026/05/22 17:56:10 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	sort_lowest_half(t_node **A, t_node **B, int half) // verander namen (three_quarter -> quarter, A vs B)
{
	t_stats *data;

	data = alloc_stats(A, B, half);
	if (!data)
		return ;
	data->three_quarter = data->quarter;
	data->h = half - 1;
	data->tq = 0;
//	print_list(*B, 'B');
	while (*B)
	{
		if (((*B)->n_index >= data->tq && \
				(*B)->n_index <= data->tq + 2) && \
				(*B)->n_index < data->three_quarter) // 0-24
			top_to_quarter(data, A, B);
		else if (((*B)->n_index <= data->h && \
				(*B)->n_index >= data->h - 2) && \
				(*B)->n_index >= data->three_quarter) // 25-49
			half_to_quarter(data, A, B);
		else // was niet de goeie
			rb(B, 0);
	}
	while (data->quarter--)
		rra(A, 0);
//	print_list(*A, 'A');
}

void	top_to_quarter(t_stats *data, t_node **A, t_node **B)
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

void	half_to_quarter(t_stats *data, t_node **A, t_node **B)
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
