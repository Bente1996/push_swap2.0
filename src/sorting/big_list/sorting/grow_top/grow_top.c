/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   grow_top.c                                              :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/09 19:42:20 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/09 19:42:48 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	grow_top(t_stats *data, t_node **a, t_node **b) // add_and_lower
{
	if ((*b)->n_index == data->lower - 1)
	{
		pa(a, b, data->top);
		data->swap++;
		//data->lower++;
	}
	else
		add_lower(data, a, b);
}

void	add_lower(t_stats *data, t_node **a, t_node **b) //handle bottom
{
	if (data->swap)
	{
		pa(a, b, data->top);
		sa(a, data->top);
		data->swap = 0;
		if (data->bottom)
		{
			if (data->bottom_stack->n_index == data->lower - 2) // wanneer er iig 1 naar boven moet
				add_new_lower(data, a);
		}
		data->lower--; // toegevoegd
	}
	else // lower geen swap
	{
		pa(a, b, data->top);
		if (data->bottom)
		{
			if (data->bottom_stack->n_index == data->lower - 1) // wanneer er iig 1 naar boven moet
				add_new_lower(data, a);
		}
	}
	data->lower--;
}
