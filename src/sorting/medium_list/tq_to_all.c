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

static void	grow_tq(t_stats *data, t_node **a, t_node **b);
static void	grow_and_swap_tq(t_stats *data, t_node **a, t_node **b);
static void	add_to_bottom(t_stats *data, t_node **a, t_node **b);

void	tq_to_all(t_stats *data, t_node **a, t_node **b)
{
	if ((*a)->n_index == data->tq)
		grow_tq(data, a, b);
	else if ((*a)->n_index == data->tq + 1 || (*a)->n_index == data->tq + 2)
		add_to_bottom(data, a, b);
}

static void	grow_tq(t_stats *data, t_node **a, t_node **b)
{
	if (!data->swap_rot)
		pb(a, b);
	else
		grow_and_swap_tq(data, a, b);
	rb(b);
	data->tq++;
}

static void	grow_and_swap_tq(t_stats *data, t_node **a, t_node **b)
{
	if (data->swap_rot == 2)
		rrb(b);
	rrb(b);
	pb(a, b);
	rb(b);
	data->bottom_stack = find_bottom(*b);
	if (data->swap_rot == 2)
	{
		if ((*b)->n_index > (*b)->next->n_index)
			sb(b);
		rb(b);
		data->swap_rot -= 2;
		data->tq += 2;
	}
	else if ((*b)->n_index == data->bottom_stack->n_index + 1)
	{
		data->tq++;
		data->swap_rot--;
	}
}

static void	add_to_bottom(t_stats *data, t_node **a, t_node **b)
{
	if (!(data->swap_rot < 2))
		return ;
	pb(a, b);
	if (!data->swap_rot || \
(data->swap_rot == 1 && (*b)->n_index > data->bottom_stack->n_index))
		data->bottom_stack = *b;
	rb(b);
	data->swap_rot++;
}
