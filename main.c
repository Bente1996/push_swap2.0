#include <stddef.h>
#include "push_swap.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_node	*list;
	//t_node *stack_b;

	//stack_b = NULL;
	if (argc < 3)
		return (1);
	list = make_list(argc, argv);
	if (!list)
		return (1);
	printf("main");
	//free_list(list);
	return (0);
}
