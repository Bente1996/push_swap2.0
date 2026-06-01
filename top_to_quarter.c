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

static void	grow_tq(t_stats *data, t_node **a, t_node **b);
static void	grow_and_swap_tq(t_stats *data, t_node **a, t_node **b);
static void	add_to_bottom(t_stats *data, t_node **a , t_node **b);

void	top_to_quarter(t_stats *data, t_node **A, t_node **B)
{
	if (!((*B)->n_index < data->quarter)) // WAAROM WERKT DIT NIET
		return ;

	if ((*B)->n_index == data->tq)
		grow_tq(data, A, B);
	else if ((*B)->n_index == data->tq + 1 || (*B)->n_index == data->tq + 2)
		add_to_bottom(data, A, B);
}

static void	grow_tq(t_stats *data, t_node **A, t_node **B)
{
	if (!data->swap_rot)
		pa(A, B, 0);
	else
		grow_and_swap_tq(data, A, B);
	ra(A, 0);
	data->tq++;
}

static void	grow_and_swap_tq(t_stats *data, t_node **A, t_node **B)
{
	if (data->swap_rot == 2)
		rra(A, 0);
	rra(A, 0);
	pa(A, B, 0);
	ra(A, 0);
	data->bottom_stack = find_bottom(*A);
	if (data->swap_rot == 2)
	{
		if ((*A)->n_index > (*A)->next->n_index)
			sa(A, 0);
		ra(A, 0);
		data->swap_rot -= 2;
		data->tq += 2;
	}
	else if ((*A)->n_index == data->bottom_stack->n_index + 1)
	{
		data->tq++;
		data->swap_rot--;
	}
}

static void	add_to_bottom(t_stats *data, t_node **A, t_node **B)
{
	if (!(data->swap_rot < 2))
		return ;
	pa(A, B, 0);
	if (!data->swap_rot || \
			(data->swap_rot == 1 && (*A)->n_index > data->bottom_stack->n_index))
		data->bottom_stack = *A;
	ra(A, 0);
	data->swap_rot++;
}
