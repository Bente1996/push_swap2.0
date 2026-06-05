/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   sb.c                                                    :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/05 21:38:09 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/05 21:38:37 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

void	sb(t_node **B)
{
	t_node	*first;
	t_node	*second;

	if (!*B || !(*B)->next)
		return ;
	first = *B;
	second = (*B)->next;
	first->next = (*B)->next->next;
	second->next = *B;
	*B = second;
	count_operations("sb");
}
