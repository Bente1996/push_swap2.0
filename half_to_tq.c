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

static void	grow_h(t_stats *data, t_node **A, t_node **B);
static void	grow_and_swap_h(t_stats *data, t_node **A, t_node **B);
static void	swap_two(t_stats *data, t_node **A, t_node **B);

void	half_to_tq(t_stats *data, t_node **A, t_node **B)
{
	if (!((*A)->n_index <= data->three_quarter)) // positief maken
		return ;
	if ((*A)->n_index == data->h)
		grow_h(data, A, B);
	else if ((*A)->n_index == data->h + 1 || (*A)->n_index == data->h + 2)
	{
		if (!(data->swap < 2)) // positief maken
			return ;
		pb(A, B);
		data->swap++;
	}
}

static void	grow_h(t_stats *data, t_node **A, t_node **B)
{
	if (data->swap)
		grow_and_swap_h(data, A, B);
	else
		pb(A, B);
	data->h++;
}

static void	grow_and_swap_h(t_stats *data, t_node **A, t_node **B)
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
}

static void	swap_two(t_stats *data, t_node **A, t_node **B)
{
	rb(B, 0);
	if ((*B)->n_index == (*A)->n_index + 1)
	{
		pb(A, B);
		sb(B);
		rrb(B);
	}
	else
	{
		rb(B, 0);
		pb(A, B);
		rrb(B);
		rrb(B);
		sb(B);
	}
	data->swap -= 2;
	data->h += 2;
}
