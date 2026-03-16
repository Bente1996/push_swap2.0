/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   main.c                                                  :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/12 20:16:17 by bede-kon            #+#    #+#           */
/*   Updated: 2026/03/12 20:16:20 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_node	*head; // Gekkigeit
	//t_node *stack_b;

	//stack_b = NULL;
	head = NULL;
	if (argc < 3)
		return (1);
	head = make_list(argc, argv);
	if (!head)
	{
		free_list(head);
		return (1);
	}
	printf("main");
	free_list(head);
	return (0);
}
