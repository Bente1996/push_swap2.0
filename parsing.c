t_node	*append_node(t_node **head, int value, int index)
{
	t_node	*new;
	t_node	*tmp;

	new = new_node(value, index);
	if (!new)
		return (NULL);
	if (duplicate(*head, value))
	{
		free (new);
		return (NULL);
	}
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	 	
	return (new);
}

int	is_number(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '-')
		i++;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	overflow(char *argv, int value, int sign)
{
	if (value < 214748364)
		return (0);
	else 
		return (1);
	if (*argv > '8')
		return (1);
	if (*argv == '8' && sign == 0)
		return (1);
	else
		return (0);
}

int	convert(char *argv, int *valid)
{
	int	value;
	int	sign;
	int	digits;

	sign = 0;
	overflow = 1;
	if (*argv == '-')
	{
		sign = -1;
		argv++;
	}
	while (*argv)
	{
		value = (*argv++ - 48 ) + value * 10;
		digits+;
		if (digits == 9)
		{
			if (overflow(argv, value, sign))
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

	valid = 0;
	if (!is_number(argv))
		return (NULL);
	*valid = 1;
	value = convert(argv);
	return (value);
}
	
t_node	*make_list(int argc, char **argv)
{
	t_node	*list;
	int	value;
	int	*valid;
	int	i;

	i = 0;
	list = NULL;
	while (i < argc)
	{
		value = make_number(argv[i], &valid);
		if (valid)
		{
			list = append_node(&list, value, i);
			if (!list)
			{
				free_list(list);
				return (NULL);
			}
		}
		else
		{
			free_list(list);
			return (NULL);
		}
	}
	return (list);
}

#include <stddef.h>

int	main(int argc, char **argv)
{
	t_node	*list;
	t_node *stack_b;

	stack_b = NULL;
	if (argc > 3)
		return (1);
	list = make_list(argc, argv);
	if (!list)
		return (1);
	free_list(list);
	return (0);
}
