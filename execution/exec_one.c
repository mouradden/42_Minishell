/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:48:28 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/23 22:37:23 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtin(t_env *env, t_cmd *cmd)
{
	if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "exit"))
		ft_exit(cmd->cmd_line);
	if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "pwd"))
		pwd();
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "echo"))
		echo(cmd->cmd_line);
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "cd"))
		cd(cmd->cmd_line[1]);
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "env"))
		ft_env(&env->envp);
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "export"))
		export(&env->envp, cmd->cmd_line);
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "unset"))
		unset(&env->envp, cmd->cmd_line[1]);
}

void	exec_one_builtin(t_env env, t_cmd *cmd)
{
	if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "exit"))
		ft_exit(cmd->cmd_line);
	if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "pwd"))
		pwd();
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "echo"))
		echo(cmd->cmd_line);
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "cd"))
		cd(cmd->cmd_line[1]);
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "env"))
		ft_env(&env.envp);
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "export"))
		export(&env.envp, cmd->cmd_line);
	else if (cmd->cmd_line[0] && !ft_strcmp(cmd->cmd_line[0], "unset"))
		unset(&env.envp, cmd->cmd_line[1]);
}

void	check_and_get_path(t_env *env, t_cmd *cmd, char **path)
{
	if (!access(cmd->cmd_line[0], X_OK))
		*path = cmd->cmd_line[0];
	else
	{
		*path = get_cmd_path(cmd->cmd_line[0], env->envp);
		if (!(*path))
		{
			ft_putstr_fd(cmd->cmd_line[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			g_exit_status = 127;
			exit(127);
		}
	}
}

void	exec_one_command(t_env *env, t_cmd *cmd, char **envp, int fdd)
{
	char		*path;
	t_redir		*redis;

	check_and_get_path(env, cmd, &path);
	redis = cmd->redir;
	while (redis)
	{
		if (redis && redis->type == ADD)
			dup_output_add(redis);
		else if (redis && redis->type == APPEND)
			dup_output_append(redis);
		else if (redis && redis->type == INPUT)
			dup_input(redis);
		else if (redis && redis->type == HERDOC)
			dup_herdoc(&fdd);
		redis = redis->next;
	}
	if (!is_builting(cmd->cmd_line[0]))
		exec_builtin(env, cmd);
	else if (cmd->cmd_line[0] && ft_strcmp(cmd->cmd_line[0], ""))
	{
		if (execve(path, cmd->cmd_line, envp) == -1)
			perror("execv");
	}
	close(fdd);
}
