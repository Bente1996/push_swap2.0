#include <stddef.h>
#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_node	*list;
	t_node *stack_b;

	stack_b = NULL;
	if (argc > 3)
		return (1);
	list = parse_input(argc, argv);
	if (!list)
		return (1);
	free_list(list);
	return (0);
}
