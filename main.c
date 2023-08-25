#include "minishell.h"

void	read_command(t_elem **elem, char *input)
{
	int				i;
	int				j;
	int				len;

	i = 0;
	while (input[i] && input[i] != '\n')
	{
		if (input[i] && is_space(input[i]))
			add_back(elem, new_elem(input, &i, 1, WHITE_SPACE));
		else if (input[i] && !is_special(input[i]))
		{
			j = i;
			len = 0;
			while (input[j] && !is_special(input[j]))
			{
				len++;
				j++;
			}
			if (input[j - 1] && input[j - 1] == '='
				&& (input[j] == '\'' || input[j] == '"'))
				parse_equal(elem, input, &i, j, len);
			else
				add_back(elem, new_elem(input, &i, len, WORD));
		}
		// else if (input[i] && input[i] == '=')
		// 	parse_equal(elem, input, &i);
		else if (input[i] && input[i] == '|')
			add_back(elem, new_elem(input, &i, 1, PIPE));
		else if (input[i] && input[i] == '\'')
			add_back(elem, new_elem(input, &i, 1, S_QUOTE));
		else if (input[i] && input[i] == '"')
			add_back(elem, new_elem(input, &i, 1, D_QUOTE));
		else if (input[i] && input[i] == '$')
		{
			len = 0;
			j = i;
			while (input[j])
			{	
				j++;
				len++;
				if (input[j] && is_special(input[j]))
					break ;
			}
			add_back(elem, new_elem(input, &i, len, VAR));
		}
		else if (input[i] && input[i] == '>' && input[i + 1] == '>')
			add_back(elem, new_elem(input, &i, 2, REDIR_APPEND));
		else if (input[i] && input[i] == '>')
			add_back(elem, new_elem(input, &i, 1, REDIR_ADD));
		else if (input[i] && input[i] == '<' && input[i + 1] == '<')
			add_back(elem, new_elem(input, &i, 2, HER_DOC));
		else if (input[i] && input[i] == '<')
			add_back(elem, new_elem(input, &i, 1, REDIR_IN));
	}
	isolate_quotes(elem);
}

void	parse_equal(t_elem **elem, char *input, int *i, int a, int len)
{
	int		j;
	int		s_q;
	int		d_q;

	j = a - 1;
	s_q = 0;
	d_q = 0;
	if (input[j] == '=' && input[j + 1]
		&& (input[j + 1] == '\'' || input[j + 1] == '"'))
	{
		if (input[j + 1] == '\'')
			s_q++;
		if (input[j + 1] == '"')
			d_q++;
		j += 2;
		while (input[j] && input[j + 1])
		{
			if (input[j] == '\'')
				s_q++;
			if (input[j] == '"')
				d_q++;
			if ((input[j] == '"' && input[j + 1] == ' ')
				|| (input[j] == '\'' && input[j + 1] == ' ')
					|| (input[j] == ' ' && (s_q % 2 == 0 || d_q % 2 == 0)))
					break ;
			len++;
			j++;
		}
		add_back(elem, new_elem(input, i, len + 2, WORD));
	}
}

void	isolate_quotes(t_elem **elem)
{
	t_elem		*cursor;

	cursor = *elem;
	while (cursor)
	{
		if (cursor && cursor->type == S_QUOTE)
		{
			cursor = cursor->next;
			while (cursor && cursor->type != S_QUOTE)
			{
				cursor->state = IN_QUOTE;
				cursor = cursor->next;
			}
		}
		if (cursor && cursor->type == D_QUOTE)
		{
			cursor = cursor->next;
			while (cursor && cursor->type != D_QUOTE)
			{
				cursor->state = IN_DQUOTE;
				cursor = cursor->next;
			}
		}
		if (cursor)
			cursor = cursor->next;
	}
}

char *ft_strcat(char *dest, char *src)
{
	int 	i;
	int 	j;
	char	*res;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
		j++;
	res = malloc(sizeof(i + j + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		res[i] = dest[i];
		i++;
	}
	while (src[j] != '\0')
	{
		res[i] = src[j];
		j++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

int main(int ac, char **av, char **envp)
{
	int status;
	char	*input;
	t_env	*env;
	t_elem	*node;
	t_envp	*envp_copy;

	(void)ac;
	(void)av;
	envp_copy = copy_env(envp);
	while(1)
	{
		env = malloc(sizeof(t_env));
		env->elem = malloc(sizeof(t_elem));
		// env = 0;
		env->elem = 0;
		env->exit_status = 0;
		env->envp = envp_copy;
		input = readline("MINISHELL $ ");
		add_history(input);
		read_command(&env->elem, input);

		
		// check_syntax_errors(env);
		if(check_syntax_errors(env))
		{	
			expand(env);
			// while (env->elem)
			// {
			// 	printf("content : %s\n", env->elem->content);
			// 	env->elem = env->elem->next;
			// }
			get_rid_of_spaces(&env->elem);
			get_rid_of_quotes(&env->elem);
				env->cmd = split_line(env->elem);
				if (env->cmd)
				{
						int i = 0;
						int		count_pipes = count_delimter_pipe(env->elem) + 1;
						// char *s = get_cmd_path(env->cmd->cmd_line[0], env->envp);
						
						if (count_pipes == 1)
						{
							if (!ft_strcmp(env->cmd->cmd_line[0], "exit"))
								break ;
							else
								exec_one_command(env, envp);
						}
						else
						{
							pid_t *pid = malloc(sizeof(pid_t) * count_pipes);
							int **fd = malloc(sizeof(int *) * (count_pipes - 1));
							if (!fd)
							{
								printf("error malloc\n");
								exit(1);
							}
							while (i < count_pipes - 1)
							{
								fd[i] = malloc(sizeof(int) * 2);
								i++;
							}
							i = 0;
							while (i < count_pipes - 1)
							{
								if (pipe(fd[i]) == -1)
									exit(EXIT_FAILURE);
								i++;
							}
							i = 0;
							while (i < count_pipes)
							{
								pid[i] = fork();
								if (pid[i] == 0)
								{
									if (env->cmd->redir)
										duplicate_fd(fd, count_pipes, i);
									exec_one_command(env, envp);

									exit(1337);
								}
								// if (env->cmd->redir)
								// 	threat_redir(env->cmd);
								env->cmd = env->cmd->next;
								i++;
							}
							i = 0;
							while (i < count_pipes - 1)
							{
								close(fd[i][0]);
								close(fd[i][1]);
								i++;
							}
							i = 0;
							while (i < count_pipes)
								waitpid(pid[i++], &status, 0);
					}
				}

				// while (env->cmd)
				// {
				// 	int i = 0;
				// 	while (env->cmd->cmd_line[i])
				// 	{
				// 		printf("cmd   |%s| **\n", env->cmd->cmd_line[i]);
				// 		i++;
				// 	}
				// 	printf("--- redir--\n");
				// 	while (env->cmd->redir)
				// 	{
				// 		printf("====>%d || %s\n", env->cmd->redir->type, env->cmd->redir->file_name);
				// 		env->cmd->redir = env->cmd->redir->next;
				// 	}
				// 	printf("---end redir--\n");
				// 			printf("--------------------\n");
				// 	env->cmd = env->cmd->next;
				// }
			// }
			while (env->elem)
			{
				node = env->elem->next;
				free(env->elem->content);
				free(env->elem);
				env->elem = node;
			}
		}
	}
	clear_history();
	return (0);
}