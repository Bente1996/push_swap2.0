/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   sort_medium_list.c                                      :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/05/25 16:48:21 by bede-kon            #+#    #+#           */
/*   Updated: 2026/05/25 17:12:45 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_medium_list(t_node **A, t_node **B, int all)
{
	int		half;

	half = all / 2;
	split_list(A, B, all / 2);
	sort_highest_half(A, B, half);
	if (UNEVEN)
		sorted_to_A(A, B, half + 1, half / 2);
	else
		sorted_to_A(A, B, half, half / 2);
	sort_lowest_half(A, B, half);
	return ;
}

void	split_list(t_node **A, t_node **B, int half)
{
	int		h;
	int		count;

	h = half;
	count = 0;
	while (h) // push to B
	{
		if ((*A)->n_index < half)
		{
			pb(A, B);
			if ((*B)->n_index < 3 || (*B)->n_index > half - 4)
			{
				rb(B, 0);
				count++;
			}
			h--;
		}
		else
			ra(A, 0);
	}
	while (count--)
		rrb(B);
}

void	sorted_to_A(t_node **A, t_node **B, int half, int quarter)
{
	quarter++;
	while (half > quarter)
	{
		rrb(B);
		pa(A, B, 0);
		half--;
	}
	while (half--)
		pa(A, B, 0);
}
