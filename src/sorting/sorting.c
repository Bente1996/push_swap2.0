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

void	sort_all(t_node **a, int all)
{
	t_node	*b;

	b = NULL;
	if (all < 3)
		sa(a);
	else if (all < 21)
		sort_small_list(a, &b, all);
	else if (all < 150)
		sort_medium_list(a, &b, all);
	else if (all < 270)
		sort_big_list(a, &b, all, 45);
	else if (all < 360)
		sort_big_list(a, &b, all, 90);
	else if (all < 450)
		sort_big_list(a, &b, all, 135);
	else
		sort_big_list(a, &b, all, 180);
}
