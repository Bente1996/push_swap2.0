#include <stdbool.h>
#include "push_swap.h"
#include "stdlib.h"

t_node	*new_node(int value, int index)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->value = value;
	new->index = index;
	new->next = NULL;
	return (new);
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


t_node	*append_node(t_node **head, int value, int index)
{
	t_node	*new;
	t_node	*tmp;

	tmp = NULL;
	if (is_duplicate(*head, value))
		return (NULL);
	new = new_node(value, index);
	if (!new)
		return (NULL);
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

bool	is_number(char *argv)
{
	if (*argv == '-')
		argv++;
	while (*argv)
	{
		if (*argv++ < '0' || *argv++ > '9')
			return (false);
	}
	return (true);
}

bool	is_overflow(char *argv, int value, int sign)
{
	if (value < 214748364)
		return (false);
	else 
		return (true);
	if (*argv > '8')
		return (true);
	if (*argv == '8' && sign == 0)
		return (true);
	else
		return (false);
}

int	convert(char *argv, int *valid)
{
	int	value;
	int	sign;
	int	digits;
	int	i;

	sign = 0;
	digits = 1;
	i = 0;
	if (*argv == '-')
	{
		sign = -1;
		argv++;
	}
	while (argv[i])
	{
		value = (*argv - 48 ) + value * 10;
		digits++;
		i++;
		if (digits == 9)
		{
			if (is_overflow(argv, value, sign))
			{
				*valid = 0;
				return (0);
			}
		}
	}
	return (value);
}

int	make_number(char *argv, int *valid)
{
	int	value;

	*valid = 0;
	if (!is_number(argv))
		return (-1);
	*valid = 1;
	value = convert(argv, valid);
	return (value);
}

#include <stdio.h>
	
t_node	*make_list(int argc, char **argv)
{
	t_node	*list;
	int	value;
	int	*valid;
	int	i;

	i = 0;
	list = NULL;
	valid = 0;
	printf("%s\n", *argv);
	while (i < argc)
	{
		value = make_number(argv[i++], valid);
		if (valid)
		{
			list = append_node(&list, value, i);
			if (!list)
			{
				free_list(&list);
				return (NULL); // return (free_list(list));
			}
		}
		else
		{
			free_list(&list);
			return (NULL); // return (free_list(list)); (is NULL)
		}
	}
	return (list);
}
