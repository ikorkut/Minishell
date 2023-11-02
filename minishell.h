/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikorkut <ikorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:40:55 by egokeri           #+#    #+#             */
/*   Updated: 2023/11/02 14:36:02 by ikorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>

# define TRUE 1
# define FALSE 0
# define DOLLAR_OP '$'
# define DOUBLE_QUOTE '"'
# define SINGLE_QUOTE '\''
# define CHILD_PROCESS 0
# define MAIN_PROCESS 1
# define REPLACE 1
# define APPEND 0

enum e_builtin_types
{
	CD = 1,
	ENV,
	PWD,
	ECHO,
	EXIT,
	UNSET,
	EXPORT
};

enum e_ttype
{
	PIPE = 1,
	STRING,
	HERE_DOC,
	RED_INPUT,
	RED_APPEND,
	RED_OUTPUT
};

typedef struct s_token
{
	char			*str;
	enum e_ttype	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_process
{
	pid_t				pid;
	int					fd[2];
	int					heredoc_fd[2];
	char				**execute;
	char				**redirects;
	struct s_process	*prev;
	struct s_process	*next;
}	t_process;

typedef struct s_minishell
{
	int			check_flag;
	int			child_pid;
	int			process_count;
	int			ignore;
	char		**env;
	char		**export;
	char		**paths;
	t_token		*token;
	t_process	*process;
}				t_minishell;

extern t_minishell	g_ms;

int			lexer(void);
int			env_len(void);
int			is_child(void);
void		start_cmd(void);
void		set_paths(void);
char		*ft_itoa(int n);
int			export_len(void);
void		free_token(void);
void		check_flag(void);
char		*get_input(void);
void		builtin_pwd(void);
void		input(char *file);
void		builtin_env(void);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
char		*dollar(char *str);
void		free_process(void);
void		close_all_fd(void);
void		print_export(void);
void		add_env(char *str);
char		*get_env(char *str);
t_process	*init_process(void);
int			child_process(void);
void		token_err(int type);
void		tokenize(char *str);
void		set_env(char **env);
char		*get_path(char *cmd);
int			check_env(char *str);
int			is_whitespace(char c);
void		add_export(char *str);
void		export_err(char *str);
void		command_err(char *str);
void		free_array(char **arr);
void		set_export(char **env);
void		no_file_err(char *str);
int			is_operator(char *str);
void		fill_all_heredoc(void);
int			check_export(char *str);
int			check_dollar(char *str);
char		*clean_quote(char *str);
int			ft_atoi(const char *str);
void		directory_err(char *str);
size_t		ft_strlen(const char *s);
void		builtin_cd(char **input);
int			is_builtin(char *command);
int			is_include_env(char *str);
void		builtin_exit(char **input);
void		builtin_echo(char **input);
char		*parse_dollar_op(char *str);
char		*ft_strdup(const char *str);
void		builtin_unset(char **input);
void		run_builtin(char **execute);
void		run_cmd(t_process *process);
int			is_include_export(char *str);
void		output(char *file, int mode);
void		builtin_export(char **input);
int			export_check_char(char *str);
void		swap_env(int pos, char *input);
void		parse_token_string(char **str);
void		heredoc(int *fd, char *endline);
char		*ft_strchr(const char *s, int c);
void		run_redirects(t_process *process);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strcat(char *dest, char *src);
void		swap_export(int pos, char *input);
void		get_all_inputs(t_process *process);
void		set_all_outputs(t_process *process);
int			contain_heredoc(t_process *process);
int			export_pos(char *str, char *export);
char		**ft_split(char const *str, char c);
void		*ft_calloc(size_t count, size_t size);
char		**push_array(char **arg_arr, char *str);
void		push_new_str(char **new_str, char *str);
t_token		*init_token(char *str, enum e_ttype type);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strcmp(const char *str1, const char *str2);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
char		*ft_substr(char const *str, unsigned int start, size_t len);
int			token_addback(t_token **token, t_token *new_token, int plus);
void		process_addback(t_process **process, t_process *new_process);

#endif
