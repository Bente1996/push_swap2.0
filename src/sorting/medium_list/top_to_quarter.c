/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   top_to_quarter.c                                        :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/05/29 15:39:18 by bede-kon            #+#    #+#           */
/*   Updated: 2026/05/29 16:25:05 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	grow_q(t_stats *data, t_node **a, t_node **b);
static void	grow_and_swap_q(t_stats *data, t_node **a, t_node **b);
static void	add_to_bottom(t_stats *data, t_node **a, t_node **b);

void	top_to_quarter(t_stats *data, t_node **a, t_node **b)
{
	if ((*b)->n_index == data->q)
		grow_q(data, a, b);
	else if ((*b)->n_index == data->q + 1 || (*b)->n_index == data->q + 2)
		add_to_bottom(data, a, b);
}

static void	grow_q(t_stats *data, t_node **a, t_node **b)
{
	if (!data->swap_rot)
		pa(a, b, 0);
	else
		grow_and_swap_q(data, a, b);
	ra(a, 0);
	data->q++;
}

static void	grow_and_swap_q(t_stats *data, t_node **a, t_node **b)
{
	if (data->swap_rot == 2)
		rra(a, 0);
	rra(a, 0);
	pa(a, b, 0);
	ra(a, 0);
	data->bottom_stack = find_bottom(*a);
	if (data->swap_rot == 2)
	{
		if ((*a)->n_index > (*a)->next->n_index)
			sa(a, 0);
		ra(a, 0);
		data->swap_rot -= 2;
		data->q += 2;
	}
	else if ((*a)->n_index == data->bottom_stack->n_index + 1)
	{
		data->q++;
		data->swap_rot--;
	}
}

static void	add_to_bottom(t_stats *data, t_node **a, t_node **b)
{
	if (!(data->swap_rot < 2))
		return ;
	pa(a, b, 0);
	if (!data->swap_rot || \
(data->swap_rot == 1 && (*a)->n_index > data->bottom_stack->n_index))
		data->bottom_stack = *a;
	ra(a, 0);
	data->swap_rot++;
}
