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
#include <stdlib.h>

t_node	*make_list(int argc, char const *const *argv, int *i, t_node **head)
{
	t_node		*list;
	int			value;
	bool		valid;

	list = NULL;
	while (*i < argc - 1)
	{
		valid = false;
		value = make_number(argv[*i + 1], &valid);
		if (!valid)
		{
			free_list(*head);
			return (NULL);
		}
		list = append_node(head, value, *i);
		if (!list)
		{
			free_list(*head);
			return (NULL);
		}
		*i += 1;
	}
	*head = sort_indices(head);
	return (*head);
}

int	make_number(char const *argv, bool *valid)
{
	int	value;

	if (!is_number(argv))
	{
		*valid = 0;
		return (0);
	}
	value = convert(argv, valid);
	return (value);
}

int	convert(char const *argv, bool *valid)
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
		if (i == 9 && argv[i] != '\0')
		{
			if (is_overflow(&argv[i], value, sign) || argv[10] != '\0')
				return (0);
		}
	}
	*valid = true;
	return (value * sign);
}
