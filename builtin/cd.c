
#include "../minishell.h"

int find_env(char *type)
{
    int i = 0;
	char **env;
	env = g_ms.env;
    while(ft_strncmp(env[i], type, ft_strlen(type)) != 0)
	{
        i++;
	}
	return (i);
}

void	set_pwd()
{
	char *old_pwd;
	int old_pwd_idx;
	int pwd_idx;

	old_pwd_idx = find_env("OLDPWD");
	pwd_idx = find_env("PWD");
	old_pwd = ft_strdup(g_ms.env[pwd_idx]);

	free(g_ms.env[pwd_idx]);
	free(g_ms.env[old_pwd_idx]);
	g_ms.env[pwd_idx] = ft_strjoin("PWD=", getcwd((void *)0, 0));
	g_ms.env[old_pwd_idx] = ft_strjoin("OLDPWD=", old_pwd + 4);
}

void	builtin_cd(char **input)
{
	char	*home;

	if (input[1] != NULL)
	{
		if (chdir(input[1]) != 0) {
			errno = 1;
			write(2, "minishell : No such file or directory\n", 38);
			strerror(errno); 
		}
	}
	else
	{
		home = getenv("HOME");
		if (home && *home) {
			if (chdir(home)) {
				perror("minishell ");
			}
		}
	}
	set_pwd();
	if (!is_parent()) {
		exit (errno);
	}
}

