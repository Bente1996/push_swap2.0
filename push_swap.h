#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdbool.h>

typedef struct s_node
{
	int		value;
	int		index;
	struct s_node	*next;
}	t_node;

t_node	*append_node(t_node **head, int value, int index);
t_node	*make_list(int argc, char **argv);
int		make_number(char *argv, int *valid);
int		convert(char *argv, int *valid);
bool	is_overflow(char *argv, int value, int sign);
bool	is_number(char *argv);
bool	is_duplicate(t_node *head, int value);
void	free_list(t_node **head);

#endif
