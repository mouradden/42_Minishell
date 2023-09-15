/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:17:19 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/15 12:06:27 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gl_exit_status = 0;

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
		else if (input[i] && input[i] == '|')
			add_back(elem, new_elem(input, &i, 1, PIPE));
		else if (input[i] && input[i] == '\'')
			add_back(elem, new_elem(input, &i, 1, S_QUOTE));
		else if (input[i] && input[i] == '"')
			add_back(elem, new_elem(input, &i, 1, D_QUOTE));
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
	// printf("|%s|\n", (*elem)->content);
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
				|| (input[j] == ' ' && ((s_q % 2 == 0 && s_q) || (d_q % 2 == 0 && d_q))))
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

char	*ft_strcat(char *dest, char *src)
{
	int		i;
	int		j;
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

int	is_builting(char *cmd)
{
	if (cmd && (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "pwd")
			|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
			|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "export")
			|| !ft_strcmp(cmd, "unset")))
		return (0);
	else
		return (1);
}

void	sig_check(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_redisplay();
		signal(sig, sig_check);
	}
	else if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		gl_exit_status = 1;
	}
}

void	sig_check_herdoc(int sig)
{
	if (sig == SIGINT)
		exit(1);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_env	env;
	int		i;
	int		count_commands;
	int		fdd;
	pid_t	pid;
	int		fd[2];
	t_cmd	*cmd;
	int		top;

	(void)ac;
	(void)av;
	env.envp = copy_env(envp);
	env.in = dup(STDIN_FILENO);
	env.out = dup(STDOUT_FILENO);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, sig_check);
		input = readline("MINISHELL $ ");
		if (!input)
		{
			// free()
			gl_exit_status = 127;
			exit(127);
		}
		add_history(input);
		env.elem = NULL;
		read_command(&env.elem, input);
		if (check_syntax_errors(&env))
		{
			expand(&env);
			get_rid_of_spaces(&env.elem);
			get_rid_of_quotes(&env.elem);
			// print_elem(&env);
			env.cmd = NULL;
			split_line(&env.cmd, &env.elem);
			// printf_cmd(&env);
			cmd = env.cmd;
			if (cmd)
			{
				i = 0;
				count_commands = count_delimter_pipe(env.elem) + 1;
				fdd = duplicate_redir(&env);
				if (count_commands == 1 && !is_builting(cmd->cmd_line[0]) && !cmd->redir)
				{
					if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "exit"))
						exit(127);
					if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "pwd"))
						pwd();
					else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "echo"))
						echo(cmd->cmd_line);
					else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "cd"))
						cd(&env, cmd->cmd_line[1]);
					else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "env"))
						ft_env(&env.envp);
					else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "export"))
						export(&env.envp, cmd->cmd_line);
					else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "unset"))
						unset(&env.envp, cmd->cmd_line[1]);
				}
				else
				{
					i = 0;
					while (i < count_commands)
					{
						pipe(fd);
						pid = fork();
						if (pid == 0)
						{
							close(fd[0]);
							if (i < count_commands - 1)
								dup2(fd[1], STDOUT_FILENO);
							exec_one_command(&env, cmd, envp, fdd);
							close(fd[1]);
							exit(0);
						}
						close(fd[1]);
						dup2(fd[0], 0);
						waitpid(pid, &gl_exit_status, WNOHANG);
						gl_exit_status = WEXITSTATUS(gl_exit_status);
						close(fd[0]);
						cmd = cmd->next;
						i++;
					}
					top = wait(&gl_exit_status);
					while (top > 0)
					{
						if (top < pid)
							gl_exit_status = WEXITSTATUS(gl_exit_status);
						top = wait(&gl_exit_status);
					}
					gl_exit_status = WEXITSTATUS(gl_exit_status);
					dup2(env.in, STDIN_FILENO);
					dup2(env.out, STDOUT_FILENO);
				}
			}
			free_env(&env, input);
		}
		// system("leaks minishell");
	}
	clear_history();
	free_envp(&env);
	return (0);
}
