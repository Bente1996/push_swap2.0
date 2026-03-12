/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parsing.c                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/12 18:21:32 by bede-kon            #+#    #+#           */
/*   Updated: 2026/03/12 18:31:12 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>

t_node	*make_list(int argc, char **argv)
{
	t_node	*list;
	int		value;
	int		*valid;
	int		i;

	i = 1;
	list = NULL;
	valid = malloc(sizeof(int));
	if (!valid)
		return (NULL);
	*valid = 0;
	while (i < argc)
	{
		value = make_number(argv[i], valid);
		printf("list: %d\n", value);
		if (!*valid)
			break ;
		list = append_node(&list, value, i);
		if (!list)
			break ;
		i++;
	}
	free (valid);
	return (list);
}

int	make_number(char *argv, int *valid)
{
	int	value;

	if (!is_number(argv))
		return (0);
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
		value = (argv[i++] - 48) + value * 10;
		if (i >= 9)
		{
			if ((i == 9 && is_overflow(&argv[i], value, sign)) \
|| (i == 10 && argv[i]))
				return (0);
		}
	}
	*valid = 1;
	return (value * sign);
}
