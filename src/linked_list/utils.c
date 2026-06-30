/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   utils.c                                                 :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/12 20:15:19 by bede-kon            #+#    #+#           */
/*   Updated: 2026/03/12 20:15:23 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "push_swap.h"

static int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	count_operations(char *operation)
{
	static int	operation_count;
	static t_text	*head;
	t_text			*current;
	t_text			*next;

	operation_count++;
	if (operation[0] == 'x')
		operation_count--;
	else if (operation[0] == 'y')
	{
		operation_count--;
		current = head;
		while (current)
		{
			write(STDOUT_FILENO, current->text, ft_strlen(current->text));
			write(STDOUT_FILENO, "\n", 1);
			next = current->next;
			free(current);
			current = next;
		}
	}
	else
		append_text(&head, operation);
	return (operation_count);
}

t_node	*sort_indices(t_node **list)
{
	t_node	*head;
	t_node	*tmp;

	head = *list;
	tmp = *list;
	while (tmp)
	{
		while (*list)
		{
			if (tmp->value > (*list)->value)
				tmp->n_index += 1;
			if (!(*list)->next)
				break ;
			*list = (*list)->next;
		}
		*list = head;
		tmp = tmp->next;
	}
	return (head);
}

int	strcmp(const char *s1, const char *s2)
{
	const unsigned char	*str1 = (unsigned char *)s1;
	const unsigned char	*str2 = (unsigned char *)s2;

	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
