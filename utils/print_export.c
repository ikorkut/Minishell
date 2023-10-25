#include "../minishell.h"

void	print_export(void)
{
	char	**env;

	env = g_ms.env;
	while (*env)
	{
		printf("declare -x %s\n", *env);
		env++;
	}
	if (!is_parent())
		exit (EXIT_SUCCESS);
}
