/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplication.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:03:54 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/17 19:50:03 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	duplicate_redir(t_env *env)
{
	int		fd;
	t_cmd	*cmd;
	t_redir	*red;

	fd = -1;
	cmd = env->cmd;
	while (cmd)
	{
		red = cmd->redir;
		while (red)
		{
			if (red->type == HERDOC)
				fork_exec_herdoc(env, red, &fd);
			red = red->next;
			if (red)
				dup2(env->in, STDIN_FILENO);
		}
		cmd = cmd->next;
	}
	return (fd);
}

void	fork_exec_herdoc(t_env *env, t_redir *red, int *fd)
{
	int		pid;

	pid = fork();
	if (pid == 0)
		execute_herdoc(env, red, fd);
	waitpid(pid, NULL, 0);
	*fd = open("/tmp/herdoc_file", O_RDONLY);
}

void	execute_herdoc(t_env *env, t_redir *red, int *fd)
{
	char	*input;

	*fd = open("/tmp/herdoc_file", O_CREAT | O_RDWR
			| O_TRUNC, S_IRUSR | S_IWUSR);
	if (!*fd)
		ft_putstr_fd("error openning file\n", 2);
	while (1)
	{
		signal(SIGINT, sig_check_herdoc);
		input = readline("> ");
		if (!input)
		{
			free(input);
			break ;
		}
		if (input && red->file_name && !ft_strcmp(input, red->file_name))
		{
			free(input);
			break ;
		}
		ft_putstr_fd(expand_input(env, input, 0), *fd);
		ft_putchar_fd('\n', *fd);
	}
	close(*fd);
	exit(1);
}

char	*expand_input(t_env *env, char *input, int index)
{
	int		len;
	char	*res;

	res = NULL;
	while (input[index])
	{
		len = index;
		while (input[len] && !is_special(input[len])
			&& input[len] != '=' && input[len] != '$')
			len++;
		res = ft_strjoin(res, extract_word(input, &index, len - index));
		if (input[len] == ' ')
			res = ft_strjoin(res, extract_word(input, &index, 1));
		if (input[index] == '$')
		{
			index++;
			len = index;
			while (input[len] && !is_special(input[len]) && input[len] != '=')
				len++;
			res = ft_strjoin(res, ft_get_env(env,
						extract_word(input, &index, len - index)));
		}
	}
	return (res);
}
