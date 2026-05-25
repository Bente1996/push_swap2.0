/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   half_to_tq.c                                            :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/05/25 16:33:08 by bede-kon            #+#    #+#           */
/*   Updated: 2026/05/25 16:41:54 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	half_to_tq(t_stats *data, t_node **A, t_node **B)
{
	if (!((*A)->n_index <= data->three_quarter))
		return ;
	if ((*A)->n_index == data->h)
		grow_h(data, A, B);
	else if ((*A)->n_index == data->h + 1 || (*A)->n_index == data->h + 2)
	{
		if (!(data->swap < 2))
			return ;
		pb(A, B);
		data->swap++;
	}
}

void	grow_h(t_stats *data, t_node **A, t_node **B)
{
	if (data->swap)
		grow_and_swap_h(data, A, B);
	else
	{
		pb(A, B);
		data->h++;
	}
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
