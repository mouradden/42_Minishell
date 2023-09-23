/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:32:11 by yoamzil           #+#    #+#             */
/*   Updated: 2023/09/23 20:27:18 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell(t_env env, char **envp)
{
	t_cmd		*cmd;
	int			fdd;

	while (1)
	{
		signal(SIGINT, sig_check);
		get_input(&env);
		if (check_syntax_errors(&env))
		{
			
			parse_elem_to_cmd(&env);
			
			cmd = env.cmd;
			if (cmd)
			{
				env.count_commands = count_delimter_pipe(env.elem) + 1;
				fdd = duplicate_redir(&env);
				if (env.count_commands == 1
					&& !is_builting(cmd->cmd_line[0]) && !cmd->redir)
					exec_one_builtin(env, cmd);
				else
					execute(&env, cmd, envp, fdd);
			}
			free_env(&env);
		}
		else
			free_elem(&env);
	}
}

void	execute(t_env *env, t_cmd *cmd, char **envp, int fdd)
{
	int		top;

	env->index_cmd = 0;
	exec_cmd(env, cmd, envp, fdd);
	top = wait(&g_exit_status);
	while (top > 0)
	{
		top = wait(&g_exit_status);
	}
	g_exit_status = WEXITSTATUS(g_exit_status);
	dup2(env->in, STDIN_FILENO);
	dup2(env->out, STDOUT_FILENO);
}

void	parse_elem_to_cmd(t_env *env)
{
	expand(env);
	print_elem(env);
	get_rid_of_spaces(&env->elem);
	get_rid_of_quotes(&env->elem);
	
	env->cmd = NULL;
	split_line(&env->cmd, &env->elem);
}

void	exec_cmd(t_env *env, t_cmd *cmd, char **envp, int fdd)
{
	pid_t	pid;
	int		fd[2];

	while (env->index_cmd < env->count_commands)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			close(fd[0]);
			if (env->index_cmd < env->count_commands - 1)
				dup2(fd[1], STDOUT_FILENO);
			exec_one_command(env, cmd, envp, fdd);
			close(fd[1]);
			exit(0);
		}
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, &g_exit_status, WNOHANG);
		g_exit_status = WEXITSTATUS(g_exit_status);
		close(fd[0]);
		cmd = cmd->next;
		env->index_cmd++;
	}
}

void	get_input(t_env *env)
{
	char		*input;

	input = readline("MINISHELL $ ");
	if (!input)
	{
		g_exit_status = 127;
		exit(127);
	}
	add_history(input);
	env->elem = NULL;
	read_command(&env->elem, input);
	free(input);
}
