#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_node
{
	int		value;
	int		index;
	struct s_node	*next;
}	t_node;

t_node	*append_node(t_node **head, int value, int index);
t_node	*make_list(int argc, char **argv);
void	free_list(t_node **head);

#endif
