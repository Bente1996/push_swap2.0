#include <stdbool.h>
#include "push_swap.h"
#include "stdlib.h"
#include <stdio.h>

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
		if (*argv++ < '0' || *argv > '9')
			return (false);
	}
	return (true);
}

bool	is_overflow(char *argv, int value, int sign) // komt binnen met 9 of 10
{
	if (value < 214748364) // 9, kan sowieso een 10e bij, 2147483647
		return (false); // false, nog een rondje
	else if (value == 214748364)
	{
		if (*argv > '8') // 10, check 10e digit
			return (true); // voorkom bouw
		if (*argv == '8' && sign == 1) // overflow, voorkom value toename
		{
			return (true);
		}
		return (false); // 10e digit was priem, nog een rondje, mag toegevoegd
	}	
	else
		return (true);	// eerste 9 digit waren groot, 10e mag niet
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
	while (argv[i] && i < 10) // alleen bouwen tm 10 digit
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

int	make_number(char *argv, int *valid)
{
	int	value;

	if (!is_number(argv))
		return (-1);
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
