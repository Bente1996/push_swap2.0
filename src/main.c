/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   main.c                                                  :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/12 20:16:17 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/08 12:34:52 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	usage(char **argv)
{
	int	err;

	err = write(STDERR_FILENO, "Usage: ", 7);
	err = write(STDERR_FILENO, argv[0], ft_strlen(argv[0]));
	err = write(STDERR_FILENO, " INTEGER INTEGER...\n", 20);
	(void)err;
	return (1);
}

int	main(int argc, char **argv)
{
	t_node	*a;
	int		index;

	a = NULL;
	index = 0;
	if (argc < 3)
		return (usage(argv));
	a = make_list(argc, argv, &index, &a);
	if (!a)
	{
		index = write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	if (!already_sorted(a))
		sort_all(&a, index);
	count_operations("y");
	free_list(a);
	return (0);
}
