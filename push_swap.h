#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_node
{
	int		value;
	int		index;
	struct s_node	*next;
}	t_node;

int	*parse_input(char *argv, int *valid);
t_node	*append_node(t_node **head, int value, int index);

#endif
