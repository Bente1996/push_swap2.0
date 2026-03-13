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
	t_node	**head = NULL; // Gekkigeit
	t_node	*list;
	//t_node *stack_b;

	//stack_b = NULL;
	if (argc < 3)
		return (1);
	list = make_list(argc, argv);
	if (!list)
		return (1);
	printf("main");
	head = &list;
	free_list(head);
	return (0);
}
