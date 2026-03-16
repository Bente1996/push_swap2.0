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
	t_node *stack_b;
	int	index;
	int	operations;

	stack_b = NULL;
	head = NULL;
	index = 0;
	if (argc < 3)
		return (1);
	head = make_list(argc, argv, &index);
	if (!head)
	{
		free_list(head);
		return (1);
	}
	operations = sorting(&head, &stack_b, index);
	//print_list(head);
	//print_list(stack_b);
	printf("%d\n", operations);
	free_list(head);
	free_list(stack_b); // later weg 
	return (0);
}
