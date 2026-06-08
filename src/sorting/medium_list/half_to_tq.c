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

static void	grow_h(t_stats *data, t_node **a, t_node **b);
static void	grow_and_swap_h(t_stats *data, t_node **a, t_node **b);
static void	swap_two(t_stats *data, t_node **a, t_node **b);

void	half_to_tq(t_stats *data, t_node **a, t_node **b)
{
	if ((*a)->n_index == data->h)
		grow_h(data, a, b);
	else if ((*a)->n_index == data->h + 1 || (*a)->n_index == data->h + 2)
	{
		if (!(data->swap < 2)) // positief maken
			return ;
		pb(a, b);
		data->swap++;
	}
}

static void	grow_h(t_stats *data, t_node **a, t_node **b)
{
	if (data->swap)
		grow_and_swap_h(data, a, b);
	else
		pb(a, b);
	data->h++;
}

static void	grow_and_swap_h(t_stats *data, t_node **a, t_node **b)
{
	if (data->swap == 1)
	{
		pb(a, b);
		sb(b);
		if ((*b)->n_index == (*b)->next->n_index + 1)
		{
			data->swap--;
			data->h++;
		}
	}
	else
		swap_two(data, a, b);
}

static void	swap_two(t_stats *data, t_node **a, t_node **b)
{
	rb(b, 0);
	if ((*b)->n_index == (*a)->n_index + 1)
	{
		pb(a, b);
		sb(b);
		rrb(b);
	}
	else
	{
		rb(b, 0);
		pb(a, b);
		rrb(b);
		rrb(b);
		sb(b);
	}
	data->swap -= 2;
	data->h += 2;
}
