/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplication.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:03:54 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/12 22:38:05 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	duplicate_fd(t_env __unused env , int __unused *fd, int __unused count_pipes, int __unused i)
{
	// if (i == 0)
	// {
	// 	close(fd[i][0]);
	// 	dup2(fd[i][1], STDOUT_FILENO);
	// 	close(fd[i][1]);	
	// }
	// else if (i == count_pipes - 1)
	// {
	// 	close(fd[i - 1][1]);
	// 	dup2(fd[i - 1][0], STDIN_FILENO);
	// 	close(fd[i - 1][0]);
	// }
	// else
	// {
	// 	close(fd[i - 1][1]);
	// 	close(fd[i][0]);
	// 	dup2(fd[i - 1][0], STDIN_FILENO);
	// 	dup2(fd[i][1], STDOUT_FILENO);
	// 	close(fd[i - 1][0]);
	// 	close(fd[i][1]);
	// }
	// i = 0;
	// while (i < count_pipes - 1)
	// {
	// 	close(fd[i][0]);
	// 	// close(fd[i][1]);
	// 	i++;
	// }
}

int	duplicate_redir(t_env *env)
{
	int		fd = -1;
	// int 	ret_fd;
	pid_t	pid;
	t_cmd	*cmd;
	t_redir	*red;

	// gl_sig = 0;
	cmd = env->cmd;
	while (cmd)
	{
		red = cmd->redir;
		while (red)
		{
			if (red->type == HERDOC)
			{
				pid = fork();
				fd = 0;
				if (pid == 0)
				{
					fd = open("/tmp/herdoc_file", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
					if (!fd)
						ft_putstr_fd("error openning file\n", 2);
					char *input;
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
						ft_putstr_fd(expand_input(env, input), fd);
						ft_putchar_fd('\n', fd);
					}
					close(fd);
					exit(1);
				}
				waitpid(pid, NULL, 0);
				fd = open("/tmp/herdoc_file", O_RDONLY);
			}
			red = red->next;
			if (red)
				dup2(env->in, STDIN_FILENO);
		}
		cmd = cmd->next;
	}
	return (fd);
}

char	*expand_input(t_env *env, char *input)
{
	int		index_dollar;
	int		index;
	int		len;
	char	*res = NULL;

	index = 0;
	while (input[index])
	{
		len = index;
		while (input[len] && !is_special(input[len])
			&& input[len] != '=' && input[len] != '$')
			len++;
		res = ft_strjoin(res, extract_word(input, &index, len - index));
		free(res);
		if (is_special(input[len]))
		{
			res = ft_strjoin(res, extract_word(input, &index, 1));
			free(res);
		}
		if (input[index] == '$')
		{
			index_dollar = check_dollar(input);
			index++;
			len = index;
			while (input[len] && !is_special(input[len]) && input[len] != '=')
				len++;
			res = ft_strjoin(res, ft_get_env(env, extract_word(input, &index, len - index)));
			free(res);
		}
	}
	return (res);
}
