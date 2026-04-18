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
	t_node	*head;
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
	if (already_sorted(head))
	{
		free_list(head);
		return (1);
	}
	operations = random_split(&head, &stack_b, index);
	//print_list(head, 'A');
	//print_list(stack_b, 'B');
	printf("Operations:%d\n", operations - 1);
	if (already_sorted(head))
		printf("GOED GESORTEERD :)");
	free_list(head);
	return (0);
}
