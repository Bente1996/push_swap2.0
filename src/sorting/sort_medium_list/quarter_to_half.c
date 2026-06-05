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

static void	grow_half(t_stats *data, t_node **A, t_node **B);
static void	grow_and_swap_half(t_stats *data, t_node **A, t_node **B);
static void	swapping_two(t_stats *data, t_node **A, t_node **B);

void	quarter_to_half(t_stats *data, t_node **A, t_node **B)
{
	 if (!((*B)->n_index >= data->quarter)) // WAAROM WERKT DIT NIET
	 	return (rb(B,0));
	if ((*B)->n_index == data->h)
		grow_half(data, A, B); // noem ook grow_h eventjes sttaic maken
	else if ((*B)->n_index == data->h - 1 || (*B)->n_index == data->h - 2)
	{
		if (!(data->swap < 2))
			return ;
		pa(A, B, 0);
		data->swap++;
	}
}

static void	grow_half(t_stats *data, t_node **A, t_node **B)
{
	if (data->swap)
		grow_and_swap_half(data, A, B);
	else
		pa(A, B, 0);
	data->h--;
}


static void	grow_and_swap_half(t_stats *data, t_node **A, t_node **B)
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
		swapping_two(data, A, B);
}

static void	swapping_two(t_stats *data, t_node **A, t_node **B)
{
	ra(A, 0);
	if ((*A)->n_index == (*B)->n_index - 1)
	{
		pa(A, B, 0);
		sa(A, 0);
		rra(A, 0);
	}
	else
	{
		ra(A, 0);
		pa(A, B, 0);
		rra(A, 0);
		rra(A, 0);
		sa(A, 0);
	}
	data->swap -= 2;
	data->h -= 2;
}
