
#include "../minishell.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*dest;

	dest = (char *)malloc((ft_strlen(str) + 1) * (sizeof(char)));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
