/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   top_to_quarter.c                                        :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/05/29 15:31:33 by bede-kon            #+#    #+#           */
/*   Updated: 2026/05/29 15:35:42 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	grow_half(t_stats *data, t_node **a, t_node **b);
static void	grow_and_swap_half(t_stats *data, t_node **a, t_node **b);
static void	swapping_two(t_stats *data, t_node **a, t_node **b);

void	quarter_to_half(t_stats *data, t_node **a, t_node **b)
{
	 if (!((*b)->n_index >= data->quarter)) // WAAROM WERKT DIT NIET
	 	return (rb(b,0));
	if ((*b)->n_index == data->h)
		grow_half(data, a, b); // noem ook grow_h eventjes sttaic maken
	else if ((*b)->n_index == data->h - 1 || (*b)->n_index == data->h - 2)
	{
		if (!(data->swap < 2))
			return ;
		pa(a, b, 0);
		data->swap++;
	}
}

static void	grow_half(t_stats *data, t_node **a, t_node **b)
{
	if (data->swap)
		grow_and_swap_half(data, a, b);
	else
		pa(a, b, 0);
	data->h--;
}


static void	grow_and_swap_half(t_stats *data, t_node **a, t_node **b)
{
	if (data->swap == 1)
	{
		pa(a, b, 0);
		sa(a, 0);
		if ((*a)->n_index == (*a)->next->n_index - 1)
		{
			data->swap--;
			data->h--;
		}
	}
	else
		swapping_two(data, a, b);
}

static void	swapping_two(t_stats *data, t_node **a, t_node **b)
{
	ra(a, 0);
	if ((*a)->n_index == (*b)->n_index - 1)
	{
		pa(a, b, 0);
		sa(a, 0);
		rra(a, 0);
	}
	else
	{
		ra(a, 0);
		pa(a, b, 0);
		rra(a, 0);
		rra(a, 0);
		sa(a, 0);
	}
	data->swap -= 2;
	data->h -= 2;
}
