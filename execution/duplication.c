/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplication.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:03:54 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/04 18:41:24 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	duplicate_fd(int **fd, int count_pipes, int i)
{
	if (i == 0)
		dup2(fd[i][1], STDOUT_FILENO);
	else if (i == count_pipes - 1)
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
	}
	else
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		dup2(fd[i][1], STDOUT_FILENO);
	}
	i = 0;
	while (i < count_pipes - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

int	duplicate_redir(t_env *env)
{
	int		fd;
	pid_t pid;
	t_cmd	*cmd;
	t_redir *red;

	gl_sig = 0;
	cmd = env->cmd;
	while (cmd)
	{
		red = cmd->redir;
		while (red)
		{
			if (red->type == HERDOC)
			{
				pid = fork();
				if (pid == 0)
				{
					fd = open("/tmp/herdoc_file", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
					if (!fd)
						ft_putstr_fd("error openning file\n", 2);
					
					char *input = "";
					// t_env *env;
					// 	env = malloc(sizeof(t_env));
					// 	env = 0;
						
					while (1)
					{	
						signal(SIGINT, sig_check_herdoc);
						input = readline("> ");
						if (!input)
							break;
						if (input && red->file_name && !ft_strcmp(input, red->file_name))
								break;
						
						ft_putstr_fd(expand_input(env, input), fd);
						ft_putchar_fd('\n', fd);
					}
					close(fd);
					fd = open("/tmp/herdoc_file", O_RDONLY);
					if (dup2(fd, STDIN_FILENO) == -1)
					{
						perror("dup2");
						ft_putstr_fd("error dpulication INPUT HERDOC\n", 2);
					}
				}
				waitpid(pid, NULL, 0);
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
	char	*res = "";

	index = 0;
	while (input[index])
	{
		len = index;
		while (input[len] && !is_special(input[len])
			&& input[len] != '=' && input[len] != '$')
				len++;
		res = ft_strjoin(res, extract_word(input, &index, len - index));
		if (is_special(input[len]))
			res = ft_strjoin(res, extract_word(input, &index, 1));
		if (input[index] == '$')
		{
			index_dollar = check_dollar(input);
			index++;
			len = index;
			while (input[len] && !is_special(input[len]) && input[len] != '=')
				len++;
			res = ft_strjoin(res, ft_get_env(env, extract_word(input, &index, len - index)));
		}
	}
	return (res);	
}