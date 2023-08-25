/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:48:28 by mdenguir          #+#    #+#             */
/*   Updated: 2023/08/25 22:37:45 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_one_command(t_env *env ,char **envp)
{
	pid_t	pid0;
	int		status;
	char	*path;

	if (!ft_strcmp(env->cmd->cmd_line[0], "pwd"))
		pwd();
	else if (!ft_strcmp(env->cmd->cmd_line[0], "echo"))
		echo(env->cmd->cmd_line);
	else if (!ft_strcmp(env->cmd->cmd_line[0], "cd"))
		cd(env->cmd->cmd_line[1]);
	else if (!ft_strcmp(env->cmd->cmd_line[0], "env"))
		ft_env(env->envp);
	else if (!ft_strcmp(env->cmd->cmd_line[0], "export"))
		export(&env->envp, env->cmd->cmd_line);
	else if (!ft_strcmp(env->cmd->cmd_line[0], "unset"))
		unset(&env->envp, env->cmd->cmd_line[1]);
	else
	{
		path = get_cmd_path(env->cmd->cmd_line[0], env->envp);
		if (!path)
		{
			dprintf(2, "command not found\n");
			exit(46);
		}
		pid0 = fork();
		if (pid0 == 0)
		{
			if (env->cmd->redir)
			{
				int n = count_redir(env->elem);
				int **fd = malloc(n * sizeof (int *));
				int i = 0;
				while (fd[i])
				{
					f[i] = malloc(2 * sizeof(int));
					fd[i] = open(env->cmd->redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
					i++;
					if (!fd[i])
						ft_putstr_fd("error openning file\n", 2);
					
					if (dup2(fd[i], STDOUT_FILENO) == -1)
						ft_putstr_fd("error duplication\n", 2);
				}
			}
			execve(path, env->cmd->cmd_line, envp);
		}
		else if (pid0 > 0)
			waitpid(pid0, &status, 0);
	}
}
