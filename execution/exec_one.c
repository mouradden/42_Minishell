/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:48:28 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/13 11:27:54 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_one_command(t_env *env, t_cmd *cmd, char **envp, int fdd)
{
	char	*path;
	int		fd;
	t_redir	*redis;

	if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "pwd"))
		pwd();
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "echo"))
		echo(cmd->cmd_line);
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "cd"))
		cd(env, cmd->cmd_line[1]);
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "env"))
		ft_env(&env->envp);
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "export"))
		export(&env->envp, cmd->cmd_line);
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "unset"))
		unset(&env->envp, cmd->cmd_line[1]);
	else
	{
		if (!access(cmd->cmd_line[0], X_OK))
			path = cmd->cmd_line[0];
		else
		{
			path = get_cmd_path(cmd->cmd_line[0], env->envp);
			if (!path)
			{
				ft_putstr_fd(cmd->cmd_line[0], 2);
				ft_putstr_fd(": command not found\n", 2);
				gl_exit_status = 127;
				exit(127);
			}
		}
		redis = cmd->redir;
		while (redis)
		{
			if (redis && redis->type == ADD)
			{
				fd = open(redis->file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
				if (!fd)
					ft_putstr_fd("error openning file\n", 2);
				if (dup2(fd, STDOUT_FILENO) == -1)
					ft_putstr_fd("error duplication ADD\n", 2);
			}
			else if (redis && redis->type == APPEND)
			{
				fd = open(redis->file_name, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
				if (!fd)
					ft_putstr_fd("error openning file\n", 2);
				if (dup2(fd, STDOUT_FILENO) == -1)
					ft_putstr_fd("error duplication APPEND \n", 2);
			}
			else if (redis && redis->type == INPUT)
			{
				if (access(redis->file_name, F_OK) == 0)
				{
					fd = open(redis->file_name, O_RDONLY | S_IRUSR);
					if (!fd)
						ft_putstr_fd("error openning file\n", 2);
					if (dup2(fd, STDIN_FILENO) == -1)
						ft_putstr_fd("error duplication INPUT\n", 2);
				}
				else
					perror(redis->file_name);
			}
			else if (redis && redis->type == HERDOC)
			{
				// dprintf(2, "-->%d\n", fdd);
				if (fdd != -1 && dup2(fdd, STDIN_FILENO) == -1)
				{
					perror("dup2");
					ft_putstr_fd("error dpulication INPUT HERDOC\n", 2);
					exit(1);
				}
			}
			redis = redis->next;
		}
		// if (!access(cmd->cmd_line[0], X_OK))
		// 	path = cmd->cmd_line[0];
		if (cmd->cmd_line[0])
		{
			if (execve(path, cmd->cmd_line, envp) == -1)
			{
				// printf("before-->%d\n", env->exit_status);
				// ft_putstr_fd(cmd->cmd_line[0], 2);
				// ft_putstr_fd(": command not found\n", 2);
				// gl_exit_status = 127;
				
				// printf("after-->%d\n", env->exit_status);
				// exit(127);
			}
		}
	}
	close(fdd);
}
