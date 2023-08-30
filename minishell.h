/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 10:34:42 by mdenguir          #+#    #+#             */
/*   Updated: 2023/08/30 15:47:39 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "readline/readline.h"
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	NORMAL,
};
enum e_token
{
	WORD,
	WHITE_SPACE,
	S_QUOTE,
	D_QUOTE,
	VAR,
	PIPE,
	REDIR_IN,
	REDIR_ADD,
	REDIR_APPEND,
	HER_DOC,
	EQUAL,
};
enum e_redir
{
	NONE,
	ADD,
	APPEND,
	INPUT,
	HERDOC,
};


typedef struct s_elem
{
	char			*content;
	int				len;
	enum e_token	type;
	enum e_state	state;
	struct s_elem	*next;
	struct s_elem	*prev;
}	t_elem;

typedef struct s_cmd
{
	char			**cmd_line;
	struct s_redir	*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_envp
{
	char			*title;
	char			*content;
	struct s_envp	*next;	
}	t_envp;

typedef struct s_env
{
	t_elem	*elem;
	t_cmd	*cmd;
	t_envp	*envp;
	int		in;
	int		out;
	int		exit_status;
}	t_env;

typedef struct s_redir
{
	enum e_redir	type;
	char			*file_name;
	struct s_redir	*next;
}	t_redir;



char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);
int		is_space(int c);
int		is_special(int c);

void	read_command(t_elem **elem, char *input);
char	*extract_word(char *input, int *index, int len);
void	isolate_quotes(t_elem **elem);
int		add_back(t_elem **elem, t_elem *new);
int		check_dollar(char *str);
t_elem	*new_elem(char *content, int *index, int len, enum e_token token);
char	*ft_strdup(char *s1);
int		count_delimter_pipe(t_elem *list);
int		count_before_pipe(t_elem *list);
int		count_nodes(t_elem *start);
t_cmd	*split_line(t_elem *list);
t_redir	*detect_redir(t_elem *start, t_elem *end);
void	add_back_redir(t_redir **redir, t_redir *new);
t_redir	*new_redir(enum e_redir type, char *file_name);

void	expand(t_env *env);
char	*remove_spaces(char *str);
int		check_syntax_errors(t_env *env);
int		check_quotes(t_env *env);
int		check_syntax_pipes(t_env *env);
int		check_consecutive_pipes(t_elem *elem);
int		check_before_pipe(t_elem *elem);
int		count_cmd(t_elem *list);
int		check_after_pipe(t_elem *elem);
int		check_invalid_redir(t_elem *elem);
int		check_redir_syntax(t_env *env);
int		invalid_consecutives_redir(t_elem *elem);
int		is_redir(t_elem *elem);
int		check_empty_redir(t_elem *elem);
int		count_redir(t_elem *list);
void	free_redir(t_redir *redir);
int		ft_strcmp_redir(char *str, t_redir *redir);
void	free_double(char **str);
t_redir	*detect_redir_final(t_elem *start);
int		is_redir_exist(t_elem *start, t_elem *end);
void	get_rid_of_spaces(t_elem **list);
char	*ft_strcat(char *dest, char *src);
void	get_rid_of_quotes(t_elem **list);

void    pwd();
void	echo(char **input);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

void    cd(char *path);
void	ft_env(t_envp *envp);
t_envp	*copy_env(char **envp);
void	split_env(t_envp **list, char *envp);
int	add_back_env(t_envp **head, t_envp *new);
char	**env_2_d(t_envp *envp);
int		count_nodes_env(t_envp *envp);
int	count_content_length(t_envp *node);
void export(t_envp **envp, char **var);
void	parse_equal(t_elem **elem, char *input, int *i, int a, int len);
char *ft_get_env(t_env *env, char *title);
int check_duplicate(t_envp **envp, char *var);
void	update_node(t_envp *envp, char *var_title, char *var_content);
void	remove_node(t_envp **envp, char *var);
void    unset(t_envp **envp, char *title);

int	count_words(const char *s, char c);
int	len_word(const char *s, char c);
char	**ft_split(char const *s, char c);

char    *get_cmd_path(char *cmd, t_envp *envp);
// void	exec_one_command(t_env *env ,char **envp);


//-----
int		duplicate_redir(t_env *env);
void	exec_one_command(t_env *env ,char **envp, int fdd);

//-----

void	duplicate_fd(int **fd, int count_pipes, int i);
// void	duplicate_redir(t_env *env);
void free_elem(t_env **env);
void	exec_one_command_herdoc(t_env *env ,char **envp);
void printf_cmd(t_env *env);
#endif