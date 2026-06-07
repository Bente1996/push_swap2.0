/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   sorting.c                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/13 15:30:43 by bede-kon            #+#    #+#           */
/*   Updated: 2026/03/13 17:40:28 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

void	sort_all(t_node **A, int all)
{
	t_node	**B;

	B = NULL;
	if (all >= 450)
		sort_big_list(A, B, all, 180);
	else if (all >= 360)
		sort_big_list(A, B, all, 135);
	else if (all >= 270)
		sort_big_list(A, B, all, 90);
	else if (all >= 150)
		sort_big_list(A, B, all, 45);
	else if (all > 20)
		sort_medium_list(A, B, all);
	else if (all > 2)
		sort_small_list(A, B, all);
	else
		sa(A, 0);
}
