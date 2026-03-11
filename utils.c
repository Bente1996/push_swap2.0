#include <stdlib.h>
#include "push_swap.h"

bool	is_number(char *argv)
{
	if (*argv == '-')
		argv++;
	while (*argv)
	{
		if (*argv++ < '0' || *argv > '9')
			return (false);
	}
	return (true);
}

bool	is_overflow(char *argv, int value, int sign)
{
	if (value < 214748364)
		return (false);
	else if (value == 214748364)
	{
		if (*argv > '8')
			return (true);
		if (*argv == '8' && sign == 1)
			return (true);
		return (false);
	}	
	else
		return (true);
}

bool	is_duplicate(t_node *head, int value)
{
	while (head)
	{
		if (head->value == value)
			return (true);
		head = head->next;
	}
	return (false);
}

void	free_list(t_node **head)
{
	t_node	*tmp;


	while (*head)
	{
		tmp = *head;
		(*head) = (*head)->next;
		free (tmp);
	}
	free (head);
}

