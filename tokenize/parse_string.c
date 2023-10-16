#include "../minishell.h"


int     count_quote(char *str, char type)
{
    int count = 0;
    while(*str)
    {
        if(*str == type)
            count++;
        str++;
    }
    return (count);
}

void	close_quote(int sig)
{
	(void)sig;
	g_ms.ignore = TRUE;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	control_quote(char **str)
{
	if(count_quote(*str, DOUBLE_QUOTE) % 2 != 0 || count_quote(*str, SINGLE_QUOTE) % 2 != 0)
	{
		while(1)
		{
			signal(SIGINT, &close_quote);
			readline(">");
			if (g_ms.ignore)
				break ;
		}
	}
}

void	find_end_pos(char **str, char type)
{
	(*str)++;
	while (**str)
	{
		if (**str == type)
		{
			(*str)++;
			if (is_whitespace(**str) || is_operator(*str))
				break ;
			else
				while (**str && !is_whitespace(**str) && !is_operator(*str))
					(*str)++;
			return ;
		}
		(*str)++;
	}
}

void	without_quote_parse(char **str)
{
	while (**str)
	{
		if (is_whitespace(**str))
			break ;
		if (is_operator(*str))
			break ;
		(*str)++;
	}
}

void	skip_whitespace(char **str, char **head)
{
	while (**str && is_whitespace(**str))
		(*str)++;
	*head = *str;
}

void	parse_token_string(char **str)
{
	int		len;
	char	*head;
	char	*token_str;

	skip_whitespace(str, &head);
	control_quote(str);
	if (**str && **str == DOUBLE_QUOTE)
		find_end_pos(str, DOUBLE_QUOTE);
	else if (**str && **str == SINGLE_QUOTE)
		find_end_pos(str, SINGLE_QUOTE);
	else
		without_quote_parse(str);
	len = *str - head;
	if (len > 0)
	{
		token_str = ft_substr(head, 0, len);
		token_addback(&g_ms.token, init_token(token_str, STRING), 0);
	}
}
