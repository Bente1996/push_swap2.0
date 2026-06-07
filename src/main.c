/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/12 20:16:17 by bede-kon            #+#    #+#           */
/*   Updated: 2026/03/12 20:16:20 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_node	*a;
	int		index;

	a = NULL;
	index = 0;
	if (argc < 3)
		return (1);
	a = make_list(argc, argv, &index);
	if (!a)
		return (1);
	sort_all(&a, index);
	free_list(a);
	return (0);
}
