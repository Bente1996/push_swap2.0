/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   swapping.c                                              :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/05/22 18:08:32 by bede-kon            #+#    #+#           */
/*   Updated: 2026/05/22 19:21:08 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	grow_tq(t_stats *data, t_node **A, t_node **B)
{
	if (!data->swap_rot)
	{
		pb(A, B);
		rb(B, 0);
		data->tq++;
	}
	else
	{
		if (data->swap_rot == 2)
			rrb(B);
		grow_and_swap_tq(data, A, B);
		data->bottom_stack = find_bottom(*B);
		data->tq++;
	}
}

void	grow_and_swap_tq(t_stats *data, t_node **A, t_node **B)
{
	if (((*A)->n_index != data->bottom_stack->n_index + 1) \
		|| data->swap_rot == 2)
		rrb(B);
	pb(A, B);
	rb(B, 0);
	data->bottom_stack = find_bottom(*B);
	if (data->swap_rot == 2)
	{
		if ((*B)->n_index > (*B)->next->n_index)
			sb(B);
		while (data->swap_rot)
		{
			rb(B, 0);
			data->swap_rot--;
			data->tq++;
		}
	}
	else if ((*B)->n_index == data->bottom_stack->n_index + 1)
	{
		rb(B, 0);
		data->tq++;
		data->swap_rot--;
	}
	else
		rb(B, 0);
}

void	grow_and_swap_h(t_stats *data, t_node **A, t_node **B)
{
	if (data->swap == 1)
	{
		pb(A, B);
		sb(B);
		if ((*B)->n_index == (*B)->next->n_index + 1)
		{
			data->swap--;
			data->h++;
		}
	}
	else
		swap_two(data, A, B);
	data->h++;
}

void	swap_two(t_stats *data, t_node **A, t_node **B)
{
	rb(B, 0);
	if ((*B)->n_index == (*A)->n_index + 1)
	{
		pb(A, B);
		sb(B);
		data->swap--;
		data->h++;
		rrb(B);
		if ((*B)->n_index == (*B)->next->n_index + 1)
		{
			data->swap--;
			data->h++;
		}
	}
	else
		more_swap(data, A, B);
}

void	more_swap(t_stats *data, t_node **A, t_node **B)
{
	rb(B, 0);
	pb(A, B);
	rrb(B);
	rrb(B);
	if ((*B)->n_index == (*B)->next->next->n_index + 1)
	{
		sb(B);
		data->swap--;
		data->h++;
		if ((*B)->n_index == (*B)->next->n_index + 1)
		{
			data->swap--;
			data->h++;
		}
	}
}
