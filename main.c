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
	t_node	*stack_a;
	t_node *stack_b;
	int	index;
	int	operations;

	stack_a = NULL;
	stack_b = NULL;
	index = 0;
	if (argc < 3)
		return (1);
	stack_a = make_list(argc, argv, &index);
	if (!stack_a)
		return (free_list(stack_a));
	if (already_sorted(stack_a))
		return (free_list(stack_a));
	sort_all(&stack_a, &stack_b, index);

	operations = count_operations("");
	print_list(stack_a, 'A');
	print_list(stack_b, 'B');
	printf("Operations:%d\n", operations - 1);
	if (already_sorted(stack_a))
		printf("GOED GESORTEERD :)");
	else
		printf("niet goed gesorteerd\n");

	printf("stacksize: %d\n", stack_size(stack_a));
	free_list(stack_a);
	return (0);
}
