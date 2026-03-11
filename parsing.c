#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>

t_node	*make_list(int argc, char **argv)
{
	t_node	*list;
	int	value;
	int	*valid;
	int	i;

	i = 1;
	list = NULL;
	valid = malloc(sizeof(int));
	if (!valid)
		return (NULL);
	*valid = 1;
	while (i < argc)
	{
		if (!*valid)
			return (NULL);
		value = make_number(argv[i], valid);
		printf("list: %d\n", value);
		if (!*valid)
			return (NULL); // + free
		list = append_node(&list, value, i);
		if (!list )
		{
			//free_list(&list); // "invalid pointer"
			return (NULL); // return (free_list(list));
		}
		i++;
	}
	//list->value = value; //test
	return (list);
}

int	make_number(char *argv, int *valid)
{
	int	value;

	if (!is_number(argv))
		return (-1);
	value = convert(argv, valid);
	return (value);
}

int	convert(char *argv, int *valid)
{
	int	value;
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	value = 0;
	if (*argv == '-')
	{
		sign = -1;
		argv++;
	}
	while (argv[i] && i < 10)
	{
		value = (argv[i] - 48) + value * 10;
		i++;
		if (i >= 9)
		{
			if ((i == 9 && is_overflow(&argv[i], value, sign)) || (i == 10 && argv[i]))
			{
				*valid = 0;
				return (0);
			}
		}
	}
	return (value * sign);
}
