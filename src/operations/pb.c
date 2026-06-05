/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   pb.c                                                    :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/05 21:32:55 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/05 21:33:36 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
#include <stddef.h>

void	pb(t_node **A, t_node **B)
{
	t_node	*tmp;

	if (!*A)
		return ;
	tmp = *A;
	*A = (*A)->next;
	tmp->next = NULL; // losgekoppeld
	if (!*B)
		*B = tmp;
	else
	{
		tmp->next = *B;
		*B = tmp;
	}
	count_operations("pb");
}
